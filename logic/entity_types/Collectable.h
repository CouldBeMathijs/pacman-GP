
#ifndef PACMAN_COLLECTABLE_H
#define PACMAN_COLLECTABLE_H
#include "Subject.h"

class Collectable : public EntityModel {
public:
    explicit Collectable(const Position& pos) : EntityModel(pos) {}
};

class Coin final : public Collectable {
public:
    explicit Coin(const Position& pos) : Collectable(pos) {}
};

class Fruit final : public Collectable {
public:
    explicit Fruit(const Position& pos) : Collectable(pos) {}
};

#endif // PACMAN_COLLECTABLE_H
