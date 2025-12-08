#include "Ghost.h"

#include "Stopwatch.h"
#include "Visitor.h"

IGhost::IGhost(const Rectangle& pos, const GhostMode start_mode, const double amountOfSecondsLeftInCurrentMode,
               const ChasingAlgorithm algorithm)
    : IEntityModel(pos, Direction::EAST), m_algorithm(algorithm), m_currentMode(start_mode), m_spawnPoint(pos.topLeft),
      m_amount_of_seconds_left_in_current_mode(amountOfSecondsLeftInCurrentMode) {}

void IGhost::accept(IEntityVisitor& visitor) { visitor.visit(*this); }

GhostMode IGhost::getMode() const { return m_currentMode; }

double IGhost::getSpeed() const { return m_speed; }

ChasingAlgorithm IGhost::getAlgorithm() const { return m_algorithm; }

void IGhost::setHitBox(const Rectangle& hb) { m_hitBox = hb; }

void IGhost::setWantedDirection(const Direction d) { m_wantedDirection = d; }

void IGhost::goToSpawn() {
    m_hitBox.moveTo(m_spawnPoint);
    m_direction = Direction::EAST;
}

void IGhost::update(const Direction direction) {
    if (m_amount_of_seconds_left_in_current_mode > 0) {
        m_amount_of_seconds_left_in_current_mode -= Stopwatch::getInstance().getDeltaTime();
    } else {
        m_currentMode = GhostMode::CHASING;
    }
    IEntityModel::update(direction);
}

BlueGhost::BlueGhost(const Rectangle& pos) : IGhost(pos, GhostMode::CHASING, 0, ChasingAlgorithm::DIRECTIONAL) {}

PinkGhost::PinkGhost(const Rectangle& pos) : IGhost(pos, GhostMode::WAITING, 5, ChasingAlgorithm::IN_FRONT_MANHATTAN) {}

OrangeGhost::OrangeGhost(const Rectangle& pos)
    : IGhost(pos, GhostMode::CHASING, 0, ChasingAlgorithm::IN_FRONT_MANHATTAN) {}

RedGhost::RedGhost(const Rectangle& pos) : IGhost(pos, GhostMode::WAITING, 10, ChasingAlgorithm::ON_TOP_MANHATTAN) {}