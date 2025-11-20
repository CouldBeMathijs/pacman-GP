#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "Subject.h"

class Pacman final : public EntityModel {
public:
    explicit Pacman(const Position& pos) : EntityModel(pos) {}
    void update(Direction) override;
    void setDirection(Direction d);
};

#endif // PACMAN_PACMAN_H
