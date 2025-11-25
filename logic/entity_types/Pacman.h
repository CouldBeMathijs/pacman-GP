#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "LogicConstants.h"
#include "Subject.h"


class Pacman final : public EntityModel {
private:
    Position spawnPoint = getHitBox().topLeft;
    bool ghostTouch = false;
    double speed = LogicConstants::BASE_SPEED;
public:
    explicit Pacman(const Rectangle& pos);
    [[nodiscard]] bool hasTouchedGhost() const;
    [[nodiscard]] double getSpeed() const;
    void accept(IEntityVisitor& visitor) override;
    void ghostTouches();
    void goToSpawn();
    void resetGhostTouch();
    void setDirection(Direction d);
    void setHitBox(const Rectangle& hb);
};

#endif // PACMAN_PACMAN_H
