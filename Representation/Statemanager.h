#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H
#include "State.h"

#include <memory>
#include <stack>

class Statemanager : public std::stack<std::unique_ptr<State>> {
public:
    Statemanager();
};

#endif // PACMAN_STATEMANAGER_H
