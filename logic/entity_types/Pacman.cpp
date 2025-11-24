#include "Pacman.h"

#include "Visitor.h"

Pacman::Pacman(const Rectangle& pos) : EntityModel(pos, Direction::EAST, PACMAN) {}
void Pacman::update(Direction d) {
    setDirection(d);
    EntityModel::update(d);
}

// You will also need a setter for position, which World uses:
void Pacman::setHitBox(const Rectangle& hb) {
    hitBox = hb;
}

void Pacman::setDirection(const Direction d) { direction = d; }

void Pacman::accept(IEntityVisitor& visitor) { visitor.visit(*this); }

double Pacman::getSpeed() const { return speed; }