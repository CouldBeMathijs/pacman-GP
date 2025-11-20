#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "Subject.h"

class Ghost : public EntityModel {
protected:
    explicit Ghost(const Position& pos) : EntityModel(pos) {}
};

class BlueGhost final : public Ghost {
public:
    explicit BlueGhost(const Position& pos) : Ghost(pos) {};
};

class PinkGhost final : public Ghost {
public:
    explicit PinkGhost(const Position& pos) : Ghost(pos) {};
};

class OrangeGhost final : public Ghost {
public:
    explicit OrangeGhost(const Position& pos) : Ghost(pos) {};
};

class RedGhost final : public Ghost {
public:
    explicit RedGhost(const Position& pos) : Ghost(pos) {};
};

#endif // PACMAN_GHOST_H
