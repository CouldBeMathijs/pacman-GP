#ifndef PACMAN_GAMEOVERSTATE_H
#define PACMAN_GAMEOVERSTATE_H
#include "AbstractState.h"
#include "Direction.h"

class GameOverState final : public AbstractState {
private:
    sf::Text m_gameOverText;
    sf::Text m_playText;
    sf::Text m_pressAnyKeyText;

public:
    void update(Direction) override;
    GameOverState();
    void handleInput(const sf::Event&) override;
};

#endif // PACMAN_GAMEOVERSTATE_H
