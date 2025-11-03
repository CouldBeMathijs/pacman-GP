#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H
#include "state/State.h"

#include <memory>
#include <stack>

class Statemanager : std::stack<std::unique_ptr<State>> {
public:
    Statemanager();
    void drawScreen(sf::RenderWindow&);
    void handleInput(const sf::Event&);
};

#endif // PACMAN_STATEMANAGER_H
