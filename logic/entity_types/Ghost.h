#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "LogicConstants.h"
#include "Subject.h"

class Ghost : public EntityModel {
protected:
    double m_speed = LogicConstants::BASE_SPEED * 0.8;

protected:
    explicit Ghost(const Rectangle& pos) : EntityModel(pos, Direction::EAST, GHOST) {}
    void accept(IEntityVisitor& visitor) override;
    [[nodiscard]] double getSpeed() const;
};

class BlueGhost final : public Ghost {
public:
    explicit BlueGhost(const Rectangle& pos) : Ghost(pos) {};
};

class PinkGhost final : public Ghost {
public:
    explicit PinkGhost(const Rectangle& pos) : Ghost(pos) {};
};

class OrangeGhost final : public Ghost {
public:
    explicit OrangeGhost(const Rectangle& pos) : Ghost(pos) {};
};

class RedGhost final : public Ghost {
public:
    explicit RedGhost(const Rectangle& pos) : Ghost(pos) {};
};

#endif // PACMAN_GHOST_H
