#ifndef PACMAN_COLLECTABLE_H
#define PACMAN_COLLECTABLE_H
#include "Subject.h"

class Collectable : public EntityModel {
public:
    explicit Collectable(const Position& pos, const Direction d, const TypeOfEntity t) : EntityModel(pos, d, t) {}
};

class Coin final : public Collectable {
public:
    explicit Coin(const Position& pos) : Collectable(pos, Direction::EAST, COIN) {}
    void accept(IEntityVisitor& visitor) override;
};

class Fruit final : public Collectable {
public:
    explicit Fruit(const Position& pos) : Collectable(pos, Direction::EAST, FRUIT) {}
    void accept(IEntityVisitor& visitor) override;
};

#endif // PACMAN_COLLECTABLE_H
