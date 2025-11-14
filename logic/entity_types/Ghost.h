#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "DirectionalEntity.h"

class Ghost final : public DirectionalEntity {
public:
    explicit Ghost(const Position& pos) : DirectionalEntity(pos, Direction::EAST) {}
};

#endif // PACMAN_GHOST_H
