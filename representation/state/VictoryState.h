
#ifndef PACMAN_VICTORYSTATE_H
#define PACMAN_VICTORYSTATE_H
#include "State.h"

class VictoryState final : public State {
public:
    void drawScreen(sf::RenderWindow&) override;
    std::unique_ptr<State> handleInput(const sf::Event&) override;
};


#endif // PACMAN_VICTORYSTATE_H
