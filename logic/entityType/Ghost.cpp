#include "Ghost.h"

#include "../patterns/Visitor.h"
#include "Stopwatch.h"

IGhost::IGhost(const Rectangle& pos, const GhostMode start_mode, const double amountOfSecondsLeftInCurrentMode,
               const ChasingAlgorithm algorithm)
    : IDirectionalEntityModel(pos, Direction::Cardinal::EAST, LogicConstants::BASE_SPEED * 0.8), m_algorithm(algorithm),
      m_currentMode(start_mode), m_amount_of_seconds_left_in_current_mode(amountOfSecondsLeftInCurrentMode) {}

void IGhost::accept(IEntityVisitor& visitor) { visitor.visit(*this); }

GhostMode IGhost::getMode() const { return m_currentMode; }

void IGhost::setMode(const GhostMode m) {
    if (m == GhostMode::PANICKING) {
        setDirection(getOpposite(getDirection()));
    }
    m_currentMode = m;
}

ChasingAlgorithm IGhost::getAlgorithm() const { return m_algorithm; }

void IGhost::setWantedDirection(const Direction::Cardinal d) { m_wantedDirection = d; }

bool IGhost::isMovingAwayFromSpawn() const { return m_isMovingAwayFromSpawn && m_currentMode != GhostMode::WAITING; }

bool IGhost::allowedToTurn() const { return m_amount_of_seconds_until_able_to_turn <= 0; }

void IGhost::goToSpawn() {
    m_direction = Direction::Cardinal::EAST;
    m_isMovingAwayFromSpawn = true;
    IDirectionalEntityModel::goToSpawn();
}

void IGhost::hasTurned() { m_amount_of_seconds_until_able_to_turn = 0.1; }

void IGhost::update(const Direction::Cardinal direction) {
    if (m_amount_of_seconds_until_able_to_turn > 0) {
        m_amount_of_seconds_until_able_to_turn -= Stopwatch::getInstance().getDeltaTime();
    }
    if (m_amount_of_seconds_left_in_current_mode > 0) {
        m_amount_of_seconds_left_in_current_mode -= Stopwatch::getInstance().getDeltaTime();
    } else {
        m_currentMode = GhostMode::CHASING;
    }
    IEntityModel::update(direction);
}

bool IGhost::isBlocked(const std::vector<std::shared_ptr<IEntityModel>>& touchingEntities) {
    const auto entity = this;
    for (const auto& target_ptr : touchingEntities) {

        if (target_ptr.get() == entity) {
            continue;
        }

        CollisionHandler entityInitiates(*entity);
        target_ptr->accept(entityInitiates);
        if (entityInitiates.getResult().moveBlocked ||
            (entityInitiates.getResult().ghostTouchingSpawnWall && !m_isMovingAwayFromSpawn)) {
            return true;
        }

        CollisionHandler targetInitiates(*target_ptr);
        entity->accept(targetInitiates);
        if (targetInitiates.getResult().moveBlocked ||
            (entityInitiates.getResult().ghostTouchingSpawnWall && !m_isMovingAwayFromSpawn)) {
            return true;
        }
    }
    return false;
}

void IGhost::hasExitedSpawn() { m_isMovingAwayFromSpawn = false; }

BlueGhost::BlueGhost(const Rectangle& pos) : IGhost(pos, GhostMode::WAITING, 5, ChasingAlgorithm::IN_FRONT_MANHATTAN) {}

PinkGhost::PinkGhost(const Rectangle& pos) : IGhost(pos, GhostMode::CHASING, 0, ChasingAlgorithm::DIRECTIONAL) {}

OrangeGhost::OrangeGhost(const Rectangle& pos)
    : IGhost(pos, GhostMode::WAITING, 0.5, ChasingAlgorithm::IN_FRONT_MANHATTAN) {}

RedGhost::RedGhost(const Rectangle& pos) : IGhost(pos, GhostMode::WAITING, 10, ChasingAlgorithm::ON_TOP_MANHATTAN) {}
