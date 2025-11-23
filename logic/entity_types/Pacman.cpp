#include "Pacman.h"

#include "Visitor.h"

void Pacman::update(Direction d) {
    switch (d) {
    case Direction::SOUTH:
        pos += {0, speed};
        break;
    case Direction::WEST:
        pos -= {speed, 0};
        break;
    case Direction::NORTH:
        pos -= {0, speed};
        break;
    case Direction::EAST:
        pos += {speed, 0};
        break;
    }
    setDirection(d);
    EntityModel::update(d);
}

void Pacman::setDirection(Direction d) { direction = d; }
void Pacman::accept(IEntityVisitor& visitor) { visitor.visit(*this); }