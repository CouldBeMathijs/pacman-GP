#include "Pacman.h"

void Pacman::update(Direction d) {
    switch (d) {
    case Direction::SOUTH:
        pos += {0, speedVertical};
        break;
    case Direction::WEST:
        pos -= {speedHorizontal, 0};
        break;
    case Direction::NORTH:
        pos -= {0, speedVertical};
        break;
    case Direction::EAST:
        pos += {speedHorizontal, 0};
        break;
    }
    setDirection(d);
    EntityModel::update(d);
}

void Pacman::setDirection(Direction d) { direction = d; }