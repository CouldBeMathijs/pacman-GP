#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "Subject.h"

class Pacman final : EntityModel {
public:
    explicit Pacman(const Position& pos) : EntityModel(pos) {}
};

#endif // PACMAN_PACMAN_H
