#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "DirectionalEntity.h"

class Pacman final : public DirectionalEntity {
public:
    explicit Pacman(const Position& pos) : DirectionalEntity(pos, Direction::EAST) {}
};

#endif // PACMAN_PACMAN_H
