#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include "Statemanager.h"
#include "World.h"

class Game {
private:
    Statemanager sm;
    World world;
public:
    void run();
};

#endif // PACMAN_GAME_H
