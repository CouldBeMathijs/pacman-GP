#include "Game.h"

#include <SFML/Graphics.hpp>

void Game::run() {
    auto& camera = Camera::getInstance();
    sf::RenderWindow& window = camera.getWindow();

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sm.empty()) {
                window.close();
                return;
            }

            camera.handleEvent(event); // Example: for resizing/view changes
            sm.handleInput(event);
        }

        // update(deltaTime);

        window.clear(sf::Color::Black);

        camera.applyView();

        sm.drawScreen(window);

        window.display();
    }
}