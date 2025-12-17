#ifndef PACMAN_PAUSEDSTATE_H
#define PACMAN_PAUSEDSTATE_H
#include "../../logic/entityType/Direction.h"
#include "IState.h"

/**
 * @brief Game State for pausing mid-game
 * * On keypress: Go back to game window
 * * On escape: Go back to main menu
 */
class PausedState final : public IState {
private:
    sf::Text m_pacmanText;
    sf::Text m_playText;

public:
    PausedState();
    void update(Direction::Cardinal) override;
    void handleInput(const sf::Event&) override;
};

#endif // PACMAN_PAUSEDSTATE_H
