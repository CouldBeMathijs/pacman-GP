
#include "MenuState.h"

#include "LevelState.h"

MenuState::MenuState() {
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
    m_playText.setString("Press any key to Play");
    m_playText.setCharacterSize(30);
    m_playText.setFillColor(sf::Color::White);

    sf::FloatRect playBounds = m_playText.getLocalBounds();
    m_playText.setOrigin(playBounds.left + playBounds.width / 2.0f,
                         playBounds.top + playBounds.height / 2.0f);
    m_playText.setPosition(800.0f / 2.0f, 400.0f);
}

void MenuState::drawScreen(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    window.draw(m_pacmanText);

    window.draw(m_playText);

    window.display();
}

std::unique_ptr<State> MenuState::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed)
    {
        return std::make_unique<LevelState>();
    } else {
        return nullptr;
    }
}
