#include "GameOverState.h"

#include "../Camera.h"
#include <stdexcept>

// Assuming 'LevelState.h' is not needed here as the game over state just pops itself
// back to the menu/previous state.

/**
 * @brief Constructor for GameOverState.
 * Initializes and positions the 'Game Over' and 'Press any key' text elements.
 */
GameOverState::GameOverState() {
    const auto& window = Camera::getInstance().getWindow();
    const sf::Vector2u windowSize = window.getSize();

    // --- Load Font ---
    if (!m_font.loadFromFile("./assets/BoldPixels/BoldPixels.ttf")) {
        // Replace with your actual error handling if different
        throw std::runtime_error("Missing font BoldPixels");
    }

    // --- Setup 'Game Over' Text ---
    m_gameOverText.setFont(m_font);
    m_gameOverText.setString("Game Over");
    m_gameOverText.setCharacterSize(80);
    m_gameOverText.setFillColor(sf::Color::Red);

    // Center the 'Game Over' text
    const sf::FloatRect gameOverBounds = m_gameOverText.getLocalBounds();
    m_gameOverText.setOrigin(gameOverBounds.left + gameOverBounds.width / 2.0f,
                             gameOverBounds.top + gameOverBounds.height / 2.0f);

    // Position 'Game Over' in the upper middle of the screen
    m_gameOverText.setPosition(windowSize.x / 2.0f, windowSize.y / 3.0f);

    // --- Setup 'Press Any Key' Text ---
    m_pressAnyKeyText.setFont(m_font);
    m_pressAnyKeyText.setString("Press any key to return to Menu");
    m_pressAnyKeyText.setCharacterSize(30);
    m_pressAnyKeyText.setFillColor(sf::Color::White);

    // Center the 'Press Any Key' text
    sf::FloatRect pressBounds = m_pressAnyKeyText.getLocalBounds();
    m_pressAnyKeyText.setOrigin(pressBounds.left + pressBounds.width / 2.0f,
                                pressBounds.top + pressBounds.height / 2.0f);

    // Position 'Press Any Key' in the lower middle of the screen
    m_pressAnyKeyText.setPosition(windowSize.x / 2.0f, windowSize.y * 2 / 3.0f);
}

/**
 * @brief Updates the state, primarily used here for drawing the elements.
 * @param d The current direction (unused in this simple state).
 */
void GameOverState::update(Direction d) {
    auto& window = Camera::getInstance().getWindow();
    window.draw(m_gameOverText);
    window.draw(m_pressAnyKeyText);
}

/**
 * @brief Handles user input.
 * Pops the current state (returns to the previous state on the stack) when any key is pressed.
 * @param event The SFML event that occurred.
 */
void GameOverState::handleInput(const sf::Event& event) {
    // Check if any key was pressed
    if (event.type == sf::Event::KeyPressed) {
        // Request to pop this state off the stack, returning to the previous state (MenuState)
        requestedPops = 1;
    }
}