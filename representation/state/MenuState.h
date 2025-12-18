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
    sf::Clock m_refreshClock;
    sf::Text m_pacmanText;
    sf::Text m_playText;
    std::vector<sf::Text> m_highScoreTexts;

public:
    MenuState();
    void update(Direction::Cardinal d) override;
    void handleInput(const sf::Event&) override;
    void setupHighScores();
};

#endif // PACMAN_MENUSTATE_H
