#include "Game.h"

#include "Camera.h"
#include "Stopwatch.h"
#include "Subject.h"

#include <SFML/Graphics.hpp>

void Game::run() {
    auto& stopwatch = Stopwatch::getInstance();

    auto& camera = Camera::getInstance();
    sf::RenderWindow& window = camera.getWindow();

    auto direction = Direction::NONE;

    while (window.isOpen()) {
        stopwatch.tick();

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || m_sm.empty()) {
                window.close();
                return;
            }
            camera.handleEvent(event);
            m_sm.handleInput(event);
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::Right:
                    direction = Direction::EAST;
                    break;
                case sf::Keyboard::Up:
                    direction = Direction::NORTH;
                    break;
                case sf::Keyboard::Left:
                    direction = Direction::WEST;
                    break;
                case sf::Keyboard::Down:
                    direction = Direction::SOUTH;
                    break;
                    default:;
                }
            }
        }
        window.clear(sf::Color::Black);
        camera.applyView();
        m_sm.update(direction);
        if (m_sm.empty()) {
            window.close();
            return;
        }
        window.display();
    }
}