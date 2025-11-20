#include "Game.h"

#include "Camera.h"
#include "Stopwatch.h"

#include <SFML/Graphics.hpp>

void Game::run() {
    auto& stopwatch = Stopwatch::getInstance();

    auto& camera = Camera::getInstance();
    sf::RenderWindow& window = camera.getWindow();

    while (window.isOpen()) {
        stopwatch.tick();

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sm.empty()) {
                window.close();
                return;
            }
            camera.handleEvent(event);
            sm.handleInput(event);
        }

        window.clear(sf::Color::Black);
        camera.applyView();
        sm.drawScreen();
        window.display();
    }
}