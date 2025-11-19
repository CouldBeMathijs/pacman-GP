
#ifndef PACMAN_GAMEOVERSTATE_H
#define PACMAN_GAMEOVERSTATE_H
#include "AbstractState.h"

class GameOverState final : public AbstractState {
public:
    void drawScreen() override;
    std::unique_ptr<AbstractState> handleInput(const sf::Event&, unsigned& amountOfPops) override;
};

#endif // PACMAN_GAMEOVERSTATE_H
