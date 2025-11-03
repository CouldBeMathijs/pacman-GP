#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include "Camera.h"
#include "Statemanager.h"

class Game {
private:
    Statemanager sm;
    Camera camera;
public:
    Game();
    void run();
};

#endif // PACMAN_GAME_H
