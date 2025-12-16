#include "Ghost.h"

#include "Stopwatch.h"
#include "Visitor.h"

IGhost::IGhost(const Rectangle& pos, const GhostMode start_mode, const double amountOfSecondsLeftInCurrentMode,
               const ChasingAlgorithm algorithm)
    : IEntityModel(pos, Direction::Cardinal::EAST), m_algorithm(algorithm), m_currentMode(start_mode),
      m_spawnPoint(pos.topLeft), m_amount_of_seconds_left_in_current_mode(amountOfSecondsLeftInCurrentMode) {}

void IGhost::accept(IEntityVisitor& visitor) { visitor.visit(*this); }

GhostMode IGhost::getMode() const { return m_currentMode; }

double IGhost::getSpeed() const { return m_speed; }

ChasingAlgorithm IGhost::getAlgorithm() const { return m_algorithm; }

void IGhost::setHitBox(const Rectangle& hb) {
    m_hitBox = hb;
}

void IGhost::setWantedDirection(const Direction::Cardinal d) {
    m_wantedDirection = d;
}

bool IGhost::allowedToTurn() const { return m_amount_of_seconds_until_able_to_turn <= 0; }

void IGhost::goToSpawn() {
    m_hitBox.moveTo(m_spawnPoint);
    m_direction = Direction::Cardinal::EAST;
}

void IGhost::hasTurned() {
    m_amount_of_seconds_until_able_to_turn = 0.1;
}

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

void IGhost::setDirection(const Direction::Cardinal d) {
    m_direction = d;
}

BlueGhost::BlueGhost(const Rectangle& pos) : IGhost(pos, GhostMode::WAITING, 5, ChasingAlgorithm::IN_FRONT_MANHATTAN) {}

PinkGhost::PinkGhost(const Rectangle& pos) : IGhost(pos, GhostMode::CHASING, 0, ChasingAlgorithm::DIRECTIONAL) {}

OrangeGhost::OrangeGhost(const Rectangle& pos)
    : IGhost(pos, GhostMode::CHASING, 0, ChasingAlgorithm::IN_FRONT_MANHATTAN) {}

RedGhost::RedGhost(const Rectangle& pos) : IGhost(pos, GhostMode::WAITING, 10, ChasingAlgorithm::ON_TOP_MANHATTAN) {}
