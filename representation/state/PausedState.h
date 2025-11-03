
#ifndef PACMAN_PAUSEDSTATE_H
#define PACMAN_PAUSEDSTATE_H
#include "State.h"

class PausedState final : public State {
public:
    void drawScreen(sf::RenderWindow&) override;
    std::unique_ptr<State> handleInput(const sf::Event&, unsigned int& amountOfPops) override;
};


#endif // PACMAN_PAUSEDSTATE_H
