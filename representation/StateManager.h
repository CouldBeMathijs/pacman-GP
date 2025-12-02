#ifndef PACMAN_STATE_MANAGER_H
#define PACMAN_STATE_MANAGER_H
#include "Direction.h"
#include "state/AbstractState.h"

#include <memory>
#include <stack>

/**
 * @brief A stack of Abstract States which provides whatever the current top state requires of it
 */
class StateManager : std::stack<std::unique_ptr<AbstractState>> {
public:
    StateManager();
    void update(Direction);
    void handleInput(const sf::Event&);
    [[nodiscard]] bool empty() const;
};

#endif
