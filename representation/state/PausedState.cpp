
#include "PausedState.h"
 PausedState::PausedState() {
    if (!m_font.loadFromFile("./assets/BoldPixels/BoldPixels.ttf")) {
        throw std::runtime_error("Missing font BoldPixels");
    }

    m_pacmanText.setFont(m_font);
    m_pacmanText.setString("Pacman");
    m_pacmanText.setCharacterSize(80);
    m_pacmanText.setFillColor(sf::Color::Yellow);

    sf::FloatRect pacmanBounds = m_pacmanText.getLocalBounds();
    m_pacmanText.setOrigin(pacmanBounds.left + pacmanBounds.width / 2.0f,
                           pacmanBounds.top + pacmanBounds.height / 2.0f);
    m_pacmanText.setPosition(800.0f / 2.0f, 150.0f);


    m_playText.setFont(m_font);
    m_playText.setString("Game paused\npress Space to continue or Esc to exit");
    m_playText.setCharacterSize(30);
    m_playText.setFillColor(sf::Color::White);

    sf::FloatRect playBounds = m_playText.getLocalBounds();
    m_playText.setOrigin(playBounds.left + playBounds.width / 2.0f,
                         playBounds.top + playBounds.height / 2.0f);
    m_playText.setPosition(800.0f / 2.0f, 400.0f);
}

void PausedState::drawScreen(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    window.draw(m_pacmanText);
    window.draw(m_playText);
    window.display();
}

std::unique_ptr<AbstractState> PausedState::handleInput(const sf::Event& event, unsigned int& amountOfPops) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            amountOfPops = 1;
        } else if (event.key.code == sf::Keyboard::Escape) {
            amountOfPops = 2;
        }
    }
    return nullptr;
}
