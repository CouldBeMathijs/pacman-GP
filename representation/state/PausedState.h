#ifndef PACMAN_PAUSEDSTATE_H
#define PACMAN_PAUSEDSTATE_H
#include "AbstractState.h"
#include "Direction.h"

class PausedState final : public AbstractState {
private:
    sf::Text m_pacmanText;
    sf::Text m_playText;
public:
    PausedState();
    void update(Direction) override;
    void handleInput(const sf::Event&) override;
};


#endif // PACMAN_PAUSEDSTATE_H
