#ifndef PACMAN_GAMEOVERSTATE_H
#define PACMAN_GAMEOVERSTATE_H
#include "AbstractState.h"
#include "Direction.h"

class GameOverState final : public AbstractState {
public:
    void update(Direction) override {};
    void handleInput(const sf::Event&) override;
};

#endif // PACMAN_GAMEOVERSTATE_H
