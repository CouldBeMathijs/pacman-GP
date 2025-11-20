
#include "MenuState.h"

#include "LevelState.h"

MenuState::MenuState() {
    const auto& window = Camera::getInstance().getWindow();
    const sf::Vector2u windowSize = window.getSize();

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

    m_pacmanText.setPosition(windowSize.x / 2.0f, windowSize. y / 4.0f);

    m_playText.setFont(m_font);
    m_playText.setString("Press any key to Play");
    m_playText.setCharacterSize(30);
    m_playText.setFillColor(sf::Color::White);

    sf::FloatRect playBounds = m_playText.getLocalBounds();
    m_playText.setOrigin(playBounds.left + playBounds.width / 2.0f,
                         playBounds.top + playBounds.height / 2.0f);

    m_playText.setPosition(windowSize.x / 2.0f, windowSize.y * 3/4.0f);
}

void MenuState::drawScreen() {
    auto& window = Camera::getInstance().getWindow();
    window.draw(m_pacmanText);
    window.draw(m_playText);
}

std::unique_ptr<AbstractState> MenuState::handleInput(const sf::Event& event, unsigned int& amountOfPops) {
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape) {
            amountOfPops = 1;
            return nullptr;
        }
        return std::make_unique<LevelState>();
    } else {
        return nullptr;
    }
}
