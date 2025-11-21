#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "LogicConstants.h"
#include "Subject.h"


class Pacman final : public EntityModel {
private:
    double speed = LogicConstants::BASE_SPEED;
public:
    explicit Pacman(const Position& pos) : EntityModel(pos) {}
    void update(Direction) override;
    void setDirection(Direction d);
};

#endif // PACMAN_PACMAN_H
