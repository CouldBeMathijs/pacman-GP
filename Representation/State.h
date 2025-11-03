#ifndef PACMAN_STATE_H
#define PACMAN_STATE_H

#include "World.h"
#include <memory>

class State {
public:
    virtual ~State() = default;

protected:
    State() = default;
};

class MenuState final : public State {

};
class LevelState final : public State {
private:
    World world;
};
class PausedState final : public State {};
class VictoryState final : public State {};

#endif // PACMAN_STATE_H
