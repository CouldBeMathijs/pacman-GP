#ifndef PACMAN_WALL_H
#define PACMAN_WALL_H
#include "Subject.h"

class Wall final : public EntityModel {
public:
    explicit Wall(const Position& pos);
    void accept(IEntityVisitor& visitor) override;
};

#endif // PACMAN_WALL_H
