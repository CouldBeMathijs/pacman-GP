#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "LogicConstants.h"
#include "Subject.h"

#define BASE_SPEED (0.01)

class Pacman final : public EntityModel {
private:
    double speedHorizontal = BASE_SPEED / LogicConstants::TARGET_ASPECT_RATIO;
    double speedVertical = BASE_SPEED * LogicConstants::TARGET_ASPECT_RATIO;
public:
    explicit Pacman(const Position& pos) : EntityModel(pos) {}
    void update(Direction) override;
    void setDirection(Direction d);
};

#endif // PACMAN_PACMAN_H
