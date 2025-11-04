#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H
#include "state/AbstractState.h"

#include <memory>
#include <stack>

class Statemanager : std::stack<std::unique_ptr<AbstractState>> {
public:
    Statemanager();
    void drawScreen(sf::RenderWindow&);
    void handleInput(const sf::Event&);
    bool empty() const;
};

#endif // PACMAN_STATEMANAGER_H
