#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "Subject.h"

class Ghost : public EntityModel {
protected:
    explicit Ghost(const Rectangle& pos) : EntityModel(pos, Direction::EAST, GHOST) {}
    void accept(IEntityVisitor& visitor) override;
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
