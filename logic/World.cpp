#include "World.h"

#include "IEntityFactory.h"
#include "LogicConstants.h"
#include "Random.h"
#include "Stopwatch.h"
#include "Visitor.h"
#include "entityType/Pacman.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <map>
#include <ranges>
#include <vector>

void World::addNonMovingEntity(std::shared_ptr<IEntityModel> e) { m_nonMovingEntities.emplace_back(std::move(e)); }

void World::addGhost(std::shared_ptr<IGhost> ghost) { m_ghosts.emplace_back(std::move(ghost)); }

const std::vector<std::shared_ptr<IEntityModel>>& World::getNonMovingEntities() const { return m_nonMovingEntities; }

std::vector<std::shared_ptr<IEntityModel>> World::getEntitiesInBounds(const Rectangle& boundBox) {
    std::vector<std::shared_ptr<IEntityModel>> results;
    // Non-moving entities within bounding box
    std::ranges::copy_if(m_nonMovingEntities,
                         std::back_inserter(results), // Efficiently adds elements to the results vector
                         [&boundBox](const std::shared_ptr<IEntityModel>& entity) {
                             // Check if the entity (which is a shared_ptr) is not null and is in bounds.
                             return entity && entity->isInBounds(boundBox);
                         });
    // Ghosts within bounding box
    std::ranges::copy_if(m_ghosts,
                         std::back_inserter(results), // Efficiently adds elements to the results vector
                         [&boundBox](const std::shared_ptr<IEntityModel>& ghost) {
                             // Check if the entity (which is a shared_ptr) is not null and is in bounds.
                             return ghost && ghost->isInBounds(boundBox);
                         });
    // Pacman if within bounding box
    if (m_pacman->isInBounds(boundBox))
        results.push_back(m_pacman);

    return results;
}

void World::setPacman(const std::shared_ptr<Pacman>& p) { m_pacman = p; }

const std::shared_ptr<Pacman>& World::getPacman() const { return m_pacman; }

/**
 * @brief Updates the state of the game world, handling Pacman's movement,
 * collision resolution, interactions (like picking up pellets), and
 * the updates of all other entities.
 *
 * @param d The direction input received from the user for Pacman's intended movement.
 */
void World::update(const Direction d) {
    auto& score = ScoreKeeper::getInstance();
    if (!m_pacman) {
        throw std::runtime_error("Pacman not defined");
    }
    if (score.collectablesLeft() == 0) {
        m_worldState = WorldState::VICTORY;
        return;
    }
    for (const auto& entity_ptr : m_nonMovingEntities) {
        entity_ptr->update(d);
    }
    ScoreKeeper::getInstance().update();

    updatePacman(d);
    updateGhosts(d);

    if (m_pacman->hasTouchedGhost()) {
        score.removeLife();
        if (score.getLives() == 0) {
            m_worldState = WorldState::GAME_OVER;
            return;
        }
        m_pacman->goToSpawn();
        m_pacman->resetGhostTouch();
    }
}

std::vector<Direction> World::possibleDirections(const std::shared_ptr<IGhost>& ghost) {
    const auto distance = ghost->getSpeed() * Stopwatch::getInstance().getDeltaTime() * 10;
    const auto hitBox = ghost->getHitBox();
    std::map<Direction, Rectangle> hitBoxesToTry = {{Direction::EAST, hitBox.movedBy(distance, 0)},
                                                    {Direction::NORTH, hitBox.movedBy(0, distance)},
                                                    {Direction::SOUTH, hitBox.movedBy(0, -distance)},
                                                    {Direction::WEST, hitBox.movedBy(-distance, 0)}};
    std::vector<Direction> out;
    for (auto [direction, hitBoxToTry] : hitBoxesToTry) {
        if (checkBlockage(hitBoxToTry, ghost))
            out.push_back(direction);
    }
    return out;
}

void World::updateGhosts(const Direction d) {
    for (const auto& ghost : m_ghosts) {
        switch (ghost->getMode()) {
        case GhostMode::CHASING: {
            if (Rectangle movedHitBox =
                    IEntityModel::calculateFutureHitBox(ghost->getHitBox(), ghost->getWantedDirection(),
                                                        ghost->getSpeed() * Stopwatch::getInstance().getDeltaTime());
                !checkBlockage(movedHitBox.scaledBy(0.90), ghost)) {
                ghost->setHitBox(movedHitBox);
                break;
            }
            switch (ghost->getAlgorithm()) {
            case ChasingAlgorithm::ON_TOP_MANHATTAN:
            case ChasingAlgorithm::IN_FRONT_MANHATTAN:
            case ChasingAlgorithm::DIRECTIONAL:
                auto possible = possibleDirections(ghost);
                if (possible.size() > 1) {
                    ghost->setWantedDirection(Random::getInstance().getRandomElement(possible));
                }
            }
            break;
        }
        case GhostMode::PANICKING:
        case GhostMode::WAITING:
            break;
        }
        ghost->update(d);
    }
}

bool World::checkBlockage(const Rectangle& rectToCheck, const std::shared_ptr<IEntityModel>& entity) {
    for (const auto blocking_targets = getEntitiesInBounds(rectToCheck); const auto& target_ptr : blocking_targets) {

        if (target_ptr.get() == entity.get())
            continue;

        CollisionHandler entityInitiates(*entity);
        target_ptr->accept(entityInitiates);
        if (entityInitiates.getResult().moveBlocked) {
            return true;
        }

        CollisionHandler targetInitiates(*target_ptr);
        entity->accept(targetInitiates);
        if (targetInitiates.getResult().moveBlocked) {
            return true;
        }
    }
    return false;
}

void World::updatePacman(Direction d) {
    constexpr double EPSILON = 0.01;
    const Rectangle current_hb = m_pacman->getHitBox();
    const double current_speed =
        std::round(60 * Stopwatch::getInstance().getDeltaTime()) * m_pacman->getSpeed() * 1.f / 60;

    if (const Direction current_direction = m_pacman->getDirection(); d != current_direction) {
        constexpr double lookahead_speed = 0.05; // Lookahead distance

        // 1. Check the intended direction normally
        const Rectangle future_hb_check_unscaled = IEntityModel::calculateFutureHitBox(current_hb, d, lookahead_speed);
        const Rectangle future_hb_check_scaled = future_hb_check_unscaled.scaledBy(1 - EPSILON);

        bool lookaheadBlocked = checkBlockage(future_hb_check_scaled, m_pacman);

        // 2. CORNER CUTTING LOGIC
        // If the direct path is blocked, check perpendicular offsets
        if (lookaheadBlocked) {
            // How many pixels/units we are willing to "slide" Pacman to catch the corner.
            // This value depends on your grid size. If tiles are 32px, 8-10 is usually good.
            constexpr double CORNER_TOLERANCE = LogicConstants::TILE_HEIGHT / 4;

            // Determine if we are moving vertically or horizontally
            const bool isVerticalChange = (d == Direction::NORTH || d == Direction::SOUTH);

            // Check offsets: Negative (Left/Up) and Positive (Right/Down)

            for (double offsets[] = {-CORNER_TOLERANCE, CORNER_TOLERANCE}; const double offset : offsets) {
                // Create a temporary "snapped" current position
                Rectangle shifted_current_hb = current_hb;

                if (isVerticalChange) {
                    shifted_current_hb.moveBy(offset, 0); // Shift X for vertical movement
                } else {
                    shifted_current_hb.moveBy(0, offset); // Shift Y for horizontal movement
                }

                // Calculate lookahead from the SHIFTED position
                Rectangle shifted_future = IEntityModel::calculateFutureHitBox(shifted_current_hb, d, lookahead_speed);

                // If this shifted path is clear, we found a corner!
                if (Rectangle shifted_check = shifted_future.scaledBy(1 - EPSILON);
                    !checkBlockage(shifted_check, m_pacman)) {
                    // Apply the snap: Move Pacman to the aligned position immediately
                    m_pacman->setHitBox(shifted_current_hb);

                    // Unblock the move so the code below processes the direction change
                    lookaheadBlocked = false;
                    break;
                }
            }
        }

        // If still blocked after trying to corner cut, revert direction
        if (lookaheadBlocked) {
            d = current_direction;
        }
    }

    // Set the (potentially modified) direction
    m_pacman->setDirection(d);

    // --- Interaction Checks ---
    handleCollectables(current_hb);

    // --- Final Movement Calculation ---
    const Rectangle future_hb = IEntityModel::calculateFutureHitBox(current_hb, d, current_speed);

    if (const auto search_future_hb = future_hb.scaledBy(1 - EPSILON); !checkBlockage(search_future_hb, m_pacman)) {
        m_pacman->setHitBox(future_hb);
    } else {
        m_pacman->setDirection(Direction::NONE);
    }

    m_pacman->update(d);
}

void World::handleCollectables(const Rectangle& current_hb) {
    for (const auto& target_ptr : getEntitiesInBounds(current_hb.scaledBy(0.2))) {
        if (target_ptr.get() == m_pacman.get())
            continue;

        CollisionHandler pacmanInitiates(*m_pacman);
        target_ptr->accept(pacmanInitiates);

        if (pacmanInitiates.getResult().interactionOccurred) {
            CollectableVisitor pickup;
            target_ptr->accept(pickup);
        }

        CollisionHandler targetInitiates(*target_ptr);
        m_pacman->accept(targetInitiates);

        if (const auto& [moveBlocked, interactionOccurred] = targetInitiates.getResult(); interactionOccurred) {
            m_pacman->ghostTouches();
        }
    }
}

WorldState World::getState() const { return m_worldState; }
