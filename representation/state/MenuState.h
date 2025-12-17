#ifndef PACMAN_MENUSTATE_H
#define PACMAN_MENUSTATE_H
#include "../../logic/entityType/Direction.h"
#include "IState.h"

/**
 * @brief Main Menu Game State, shows the High Scores and starts up with the main game window
 * * On keypress: Start Level State
 * * On escape: Request deletion and quit the game
 */
class MenuState final : public IState {
private:
    sf::Text m_pacmanText;
    sf::Text m_playText;

public:
    MenuState();
    void update(Direction::Cardinal d) override;
    void handleInput(const sf::Event&) override;
};

#endif // PACMAN_MENUSTATE_H
