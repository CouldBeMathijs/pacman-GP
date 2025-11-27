#ifndef PACMAN_VICTORYSTATE_H
#define PACMAN_VICTORYSTATE_H

#include "AbstractState.h"
#include <SFML/Graphics.hpp>

class VictoryState : public AbstractState {
public:
    /**
     * @brief Constructor for VictoryState.
     */
    VictoryState();

    /**
     * @brief Draws the text elements to the window.
     * @param d The current direction (often unused in menu/info states).
     */
    void update(Direction d) override;

    /**
     * @brief Handles user input (e.g., key presses).
     * @param event The SFML event that occurred.
     */
    void handleInput(const sf::Event& event) override;

private:
    sf::Font m_font;
    sf::Text m_victoryText;
    sf::Text m_pressAnyKeyText;
    unsigned int m_level = 0;
};

#endif // PACMAN_VICTORYSTATE_H
