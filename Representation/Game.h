#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include "Camera.h"
#include "Statemanager.h"
#include "World.h"

class Game {
private:
    Statemanager sm;
    World world;
    Camera camera;
public:
    Game();
    void run();
};

#endif // PACMAN_GAME_H
