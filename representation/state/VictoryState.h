#ifndef PACMAN_VICTORYSTATE_H
#define PACMAN_VICTORYSTATE_H
#include "AbstractState.h"

class VictoryState final : public AbstractState {
public:
    void update(Direction) override {}
    void handleInput(const sf::Event&) override;
};


#endif // PACMAN_VICTORYSTATE_H
