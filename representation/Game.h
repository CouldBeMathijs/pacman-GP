#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include "Camera.h"
#include "Statemanager.h"

class Game {
private:
    Statemanager sm;
public:
    Game() = default;
    void run();
};

#endif // PACMAN_GAME_H
