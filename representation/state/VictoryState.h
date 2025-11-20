
#ifndef PACMAN_VICTORYSTATE_H
#define PACMAN_VICTORYSTATE_H
#include "AbstractState.h"

class VictoryState final : public AbstractState {
public:
    void update(Direction) override {}
    std::unique_ptr<AbstractState> handleInput(const sf::Event&, unsigned int& amountOfPops) override;
};


#endif // PACMAN_VICTORYSTATE_H
