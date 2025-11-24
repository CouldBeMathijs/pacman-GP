#include "Pacman.h"

#include "Visitor.h"

void Pacman::update(Direction d) {
    // 1. Only handle direction change.
    setDirection(d);

    // 2. Call the base class update for any non-collision, non-movement updates
    // (e.g., animation state, timer updates).
    EntityModel::update(d);

    // The previous movement logic (pos += {..., ...}) is GONE.
}

// You will also need a setter for position, which World uses:
void Pacman::setPosition(const Position& p) {
    pos = p;
}

void Pacman::setDirection(const Direction d) { direction = d; }

void Pacman::accept(IEntityVisitor& visitor) { visitor.visit(*this); }

double Pacman::getSpeed() const { return speed; }