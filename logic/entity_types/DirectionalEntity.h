
#ifndef PACMAN_DIRECTIONALENTITY_H
#define PACMAN_DIRECTIONALENTITY_H
#include "Subject.h"

enum class Direction {
    EAST,
    NORTH,
    WEST,
    SOUTH
};

class DirectionalEntity : public EntityModel {
private:
    Direction direction;
public:
    DirectionalEntity(const Position& pos, const Direction direction) : EntityModel(pos), direction(direction) {}
    [[nodiscard]] Direction getDirection() const;
};

#endif // PACMAN_DIRECTIONALENTITY_H
