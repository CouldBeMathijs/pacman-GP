#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include "Statemanager.h"

class Game {
private:
    Statemanager sm;
public:
    void run();
};

#endif // PACMAN_GAME_H
