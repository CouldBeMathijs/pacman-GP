#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "Subject.h"

class Ghost final : EntityModel {
public:
    explicit Ghost(const Position& pos) : EntityModel(pos) {}
};



#endif // PACMAN_GHOST_H
