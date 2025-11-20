#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H
#include "Direction.h"
#include "state/AbstractState.h"

#include <memory>
#include <stack>

class Statemanager : std::stack<std::unique_ptr<AbstractState>> {
public:
    Statemanager();
    void update(Direction);
    void handleInput(const sf::Event&);
    [[nodiscard]] bool empty() const;
};

#endif // PACMAN_STATEMANAGER_H
