#include "Pacman.h"

#include "Visitor.h"

Pacman::Pacman(const Rectangle& pos)
    : IDirectionalEntityModel(pos, Direction::Cardinal::NONE, LogicConstants::BASE_SPEED) {}

bool Pacman::isDying() const { return m_isDying; }

void Pacman::goToSpawn() {
    setDirection(Direction::Cardinal::NONE);
    IDirectionalEntityModel::goToSpawn();
}

void Pacman::accept(IEntityVisitor& visitor) { visitor.visit(*this); }

void Pacman::ghostTouches() { m_ghostTouch = true; }

void Pacman::resetGhostTouch() { m_ghostTouch = false; }

bool Pacman::hasTouchedGhost() const { return m_ghostTouch; }