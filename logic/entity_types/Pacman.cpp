#include "Pacman.h"

#include <set>
void Pacman::update(Direction d) {
    setDirection(d);
    EntityModel::update(d);
}

void Pacman::setDirection(Direction d) {
    direction = d;
}