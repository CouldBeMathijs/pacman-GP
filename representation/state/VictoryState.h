#ifndef PACMAN_VICTORYSTATE_H
#define PACMAN_VICTORYSTATE_H

#include "IState.h"
#include <SFML/Graphics.hpp>

/**
 * @brief Shows level completed screen
 * * On keypress: go to new Level State
 */
class VictoryState final : public IState {
private:
    sf::Text m_victoryText;
    sf::Text m_pressAnyKeyText;
    unsigned int m_level;

public:
    /**
     * @brief Constructor for VictoryState.
     */
    explicit VictoryState(unsigned int level);

    /**
     * @brief Draws the text elements to the window.
     * @param d The current direction (often unused in menu/info states).
     */
    void update(Direction::Cardinal d) override;

    /**
     * @brief Handles user input (e.g., key presses).
     * @param event The SFML event that occurred.
     */
    void handleInput(const sf::Event& event) override;
};

#endif // PACMAN_VICTORYSTATE_H
