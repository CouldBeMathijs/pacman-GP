#ifndef PACMAN_GAMEOVERSTATE_H
#define PACMAN_GAMEOVERSTATE_H
#include "../../logic/entityType/Direction.h"
#include "IState.h"

/**
 * @brief Game state to Game Over text
 * * On keypress: return to menu
 */
class GameOverState final : public IState {
    const unsigned int m_finalScore;
    sf::Text m_gameOverText;
    sf::Text m_playText;
    sf::Text m_pressAnyKeyText;

public:
    void update(Direction::Cardinal) override;
    explicit GameOverState(unsigned int finalScore);
    void handleInput(const sf::Event&) override;
};

#endif // PACMAN_GAMEOVERSTATE_H
