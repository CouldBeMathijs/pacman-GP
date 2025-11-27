#include "Pacman.h"

#include "Visitor.h"

Pacman::Pacman(const Rectangle& pos) : EntityModel(pos, Direction::NONE, PACMAN) {}
// You will also need a setter for position, which World uses:
void Pacman::setHitBox(const Rectangle& hb) {
    hitBox = hb;
}
void Pacman::goToSpawn() {
    hitBox.moveTo(spawnPoint);
    setDirection(Direction::NONE);
}

void Pacman::setDirection(const Direction d) { direction = d; }

void Pacman::accept(IEntityVisitor& visitor) { visitor.visit(*this); }

double Pacman::getSpeed() const { return speed; }

void Pacman::ghostTouches() { ghostTouch = true; }
void Pacman::resetGhostTouch() { ghostTouch = false; }
bool Pacman::hasTouchedGhost() const { return ghostTouch; }