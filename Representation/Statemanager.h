#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H
#include "State.h"

#include <stack>

class Statemanager {
private:
    std::stack<State> states;
public:
    Statemanager() = default;
};

#endif // PACMAN_STATEMANAGER_H
