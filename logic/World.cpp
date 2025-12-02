#include "World.h"

#include "AbstractEntityFactory.h"
#include "LogicConstants.h"
#include "Visitor.h"
#include "entity_types/Pacman.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>

void World::addEntity(std::shared_ptr<EntityModel> e) { m_entities.emplace_back(std::move(e)); }
std::vector<std::shared_ptr<EntityModel>> World::getEntities() { return m_entities; }

std::vector<std::shared_ptr<EntityModel>> World::getEntitiesInBounds(const Rectangle& boundBox) {
    std::vector<std::shared_ptr<EntityModel>> results;

    std::ranges::copy_if(m_entities,
                         std::back_inserter(results), // Efficiently adds elements to the results vector
                         [&boundBox](const std::shared_ptr<EntityModel>& entity) {
                             // Check if the entity (which is a shared_ptr) is not null and is in bounds.
                             return entity && entity->isInBounds(boundBox);
                         });

    return results;
}
void World::setPacman(const std::shared_ptr<Pacman>& p) { m_pacman = p; }
std::shared_ptr<Pacman> World::getPacman() { return m_pacman; }

/**
 * @brief Updates the state of the game world, handling Pacman's movement,
 * collision resolution, interactions (like picking up pellets), and
 * the updates of all other entities.
 *
 * @param d The direction input received from the user for Pacman's intended movement.
 */
void World::update(Direction d) {
    auto& score = ScoreKeeper::getInstance();
    if (!m_pacman) {
        throw std::runtime_error("Pacman not defined");
    }
    if (score.collectablesLeft() == 0) {
        m_worldState = WorldState::VICTORY;
        return;
    }
    for (const auto& entity_ptr : m_entities) {
        entity_ptr->update(d);
    }
    if (m_pacman->hasTouchedGhost()) {
        score.removeLife();
        if (score.getLives() == 0) {
            m_worldState = WorldState::GAME_OVER;
            return;
        }
        m_pacman->goToSpawn();
        m_pacman->resetGhostTouch();
    }
    {
        constexpr double EPSILON = 0.01;
        const Rectangle current_hb = m_pacman->getHitBox();
        const double current_speed = m_pacman->getSpeed();

        if (const Direction current_direction = m_pacman->getDirection(); d != current_direction) {
            const double lookahead_speed = current_speed * 10.0;

            // Calculate the position after the lookahead distance in the *new* direction 'd'.
            // The starting point for the check is a scaled-down version of the current hitbox.
            const Rectangle future_hb_check_unscaled =
                EntityModel::calculateFutureHitBox(current_hb, d, lookahead_speed);

            // Apply a scale for more forgiving lookahead collision detection
            const Rectangle future_hb_check_scaled = future_hb_check_unscaled.scaledBy(1 - EPSILON);

            bool lookaheadBlocked = false;

            // Check for blocking entities (like walls) at the lookahead position.
            for (const auto blocking_targets = getEntitiesInBounds(future_hb_check_scaled);
                 const auto& target_ptr : blocking_targets) {

                // Use CollisionHandler to check for a *blocking* collision.
                CollisionHandler handler(*m_pacman);
                target_ptr->accept(handler);

                if (handler.getResult().moveBlocked) {
                    lookaheadBlocked = true;
                    break;
                }
            }

            // If the lookahead is blocked, REJECT the new direction 'd'.
            if (lookaheadBlocked) {
                d = current_direction;
            }
        }

        // Set the (potentially modified) direction for the rest of the update
        m_pacman->setDirection(d);

        {
            // Define the bounding box at the CURRENT position for interaction checks.
            const auto interaction_targets = getEntitiesInBounds(current_hb);

            for (const auto& target_ptr : interaction_targets) {
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

                const CollisionResult& rev = targetInitiates.getResult();

                if (rev.interactionOccurred) {
                    m_pacman->ghostTouches();
                }
            }
        }

        // Calculate the future position based on the (potentially modified) direction 'd'.
        const Rectangle future_hb = EntityModel::calculateFutureHitBox(current_hb, d, current_speed);

        bool moveBlocked = false;

        // Use the requested scaled-down hitbox for collision detection at the future position.
        const auto search_future_hb = future_hb.scaledBy(1 - EPSILON);

        // Collision Resolution Loop (Movement Block Only)
        for (const auto blocking_targets = getEntitiesInBounds(search_future_hb);
             const auto& target_ptr : blocking_targets) {
            if (target_ptr.get() == m_pacman.get())
                continue;

            // Use the CollisionHandler specifically to check for *blocking* entities (like walls).
            CollisionHandler handler(*m_pacman);
            target_ptr->accept(handler);
            const CollisionResult& result = handler.getResult();

            if (result.moveBlocked) {
                moveBlocked = true;
                break; // Stop checking if movement is blocked.
            }
        }

        if (!moveBlocked) {
            // Position is updated.
            m_pacman->setHitBox(future_hb);
        } else {
            m_pacman->setDirection(Direction::NONE);
        }

        m_pacman->update(d);
    }
}

WorldState World::getState() const { return m_worldState; }

World WorldCreator::createWorldFromFile(const std::string& filename,
                                        const std::shared_ptr<AbstractEntityFactory>& factory) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        throw std::runtime_error(filename + " was not opened successfully...");
    }

    std::vector<std::vector<char>> gridData;
    std::string line;

    // 1. Read the file into gridData (Correct: gridData[row][column])
    while (std::getline(inputFile, line)) {
        std::vector<char> row;
        for (char c : line) {
            row.push_back(c);
        }
        gridData.push_back(std::move(row));
    }

    inputFile.close();

    // Ensure the map is not empty
    if (gridData.empty() || gridData[0].empty()) {
        throw std::runtime_error("World map is empty.");
    }

    // 2. Define dimensions clearly
    size_t num_rows_y = gridData.size();    // Y-dimension (height)
    size_t num_cols_x = gridData[0].size(); // X-dimension (width)

    // 3. Validate map consistency
    for (const auto& row : gridData) {
        if (num_cols_x != row.size()) {
            throw std::runtime_error("Invalid world map; every line must have the same number of characters");
        }
    }

    // Building the world object
    World out;
    auto& score = ScoreKeeper::getInstance();

    // 4. Loop in the standard [Y][X] order (Row by Row, then Column by Column)
    for (size_t y = 0; y < num_rows_y; y++) {     // Loop over rows (Y coordinate)
        for (size_t x = 0; x < num_cols_x; x++) { // Loop over columns (X coordinate)

            // Step A: Calculate the top-left corner of the current grid cell (x, y)
            // This represents the start of the cell.
            Position pos_start =
                Position(static_cast<double>(x), static_cast<double>(y))
                    .rescale({0, 0}, {static_cast<double>(num_cols_x), static_cast<double>(num_rows_y)},
                             {-1, -LogicConstants::REVERSE_TARGET_ASPECT_RATIO},
                             {1, LogicConstants::REVERSE_TARGET_ASPECT_RATIO});

            // Step B: Calculate the bottom-right corner of the current grid cell (x+1, y+1)
            // This represents the end of the cell.
            Position pos_end = Position(static_cast<double>(x + 1), static_cast<double>(y + 1))
                                   .rescale({0, 0}, {static_cast<double>(num_cols_x), static_cast<double>(num_rows_y)},
                                            {-1, -LogicConstants::REVERSE_TARGET_ASPECT_RATIO},
                                            {1, LogicConstants::REVERSE_TARGET_ASPECT_RATIO});

            // Hitbox (hb) spans the entire grid cell (100% size) for ALL entities,
            // ensuring they are all the same size relative to the grid.
            Rectangle hb = {pos_start, pos_end};
            Rectangle hb_coin = hb.scaledBy(0.2);

            // Access the grid using [row][column] which is [y][x]
            switch (gridData[y][x]) {
            case '#':
                out.addEntity(factory->createWall(hb));
                break;
            case '*': {
                auto c = factory->createCoin(hb_coin);
                score.addCollectable();
                out.addEntity(std::move(c));
            } break;
            case 'F': {
                auto f = factory->createFruit(hb);
                score.addCollectable();
                out.addEntity(std::move(f));
            } break;
            case 'P':
                out.setPacman(std::static_pointer_cast<Pacman>(factory->createPacman(hb)));
                break;
            case '1':
                out.addEntity(factory->createBlueGhost(hb));
                break;
            case '2':
                out.addEntity(factory->createPinkGhost(hb));
                break;
            case '3':
                out.addEntity(factory->createOrangeGhost(hb));
                break;
            case '4':
                out.addEntity(factory->createRedGhost(hb));
                break;
            default:
                // Do nothing for empty space ' '
                break;
            }
        }
    }
    ScoreKeeper::getInstance().nextLevel();
    return out;
}