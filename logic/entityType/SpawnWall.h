#ifndef PACMAN_SPAWN_WALL_H
#define PACMAN_SPAWN_WALL_H
#include "IEntityModel.h"

class SpawnWall : public IEntityModel {
public:
    explicit SpawnWall(const Rectangle& hitBox);
    void accept(IEntityVisitor& visitor);
};

#endif
