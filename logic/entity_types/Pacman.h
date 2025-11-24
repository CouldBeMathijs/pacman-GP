#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "LogicConstants.h"
#include "Subject.h"


class Pacman final : public EntityModel {
private:
    double speed = LogicConstants::BASE_SPEED;
public:
    explicit Pacman(const Position& pos);
    void update(Direction) override;
    void setPosition(const Position& p);
    void setDirection(Direction d);
    void accept(IEntityVisitor& visitor) override;
    [[nodiscard]] double getSpeed() const;
};

#endif // PACMAN_PACMAN_H
