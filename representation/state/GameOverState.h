#ifndef PACMAN_GAMEOVERSTATE_H
#define PACMAN_GAMEOVERSTATE_H
#include "AbstractState.h"
#include "Direction.h"

class GameOverState final : public AbstractState {
public:
    void update(Direction) override;
    std::unique_ptr<AbstractState> handleInput(const sf::Event&, unsigned& amountOfPops) override;
};

#endif // PACMAN_GAMEOVERSTATE_H
