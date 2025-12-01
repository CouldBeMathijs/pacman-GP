#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include "StateManager.h"

class Game {
private:
    StateManager m_sm;

public:
    Game() = default;
    void run();
};

#endif // PACMAN_GAME_H
