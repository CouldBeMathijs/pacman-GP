#include "Pacman.h"

#include "Visitor.h"

Pacman::Pacman(const Rectangle& pos) : IEntityModel(pos, Direction::NONE) {}

void Pacman::setHitBox(const Rectangle& hb) { m_hitBox = hb; }

bool Pacman::isDying() const { return m_isDying; }

void Pacman::goToSpawn() {
    m_hitBox.moveTo(m_spawnPoint);
    setDirection(Direction::NONE);
}

void Pacman::setDirection(const Direction d) { m_direction = d; }

void Pacman::accept(IEntityVisitor& visitor) { visitor.visit(*this); }

double Pacman::getSpeed() const { return m_speed; }

void Pacman::ghostTouches() { m_ghostTouch = true; }

void Pacman::resetGhostTouch() { m_ghostTouch = false; }

bool Pacman::hasTouchedGhost() const { return m_ghostTouch; }