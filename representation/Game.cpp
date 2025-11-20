#include "Game.h"

#include "Camera.h"
#include "Stopwatch.h"

#include <SFML/Graphics.hpp>

void Game::run() {
    // Get the singleton instance of the Stopwatch
    auto& stopwatch = Stopwatch::getInstance();

    auto& camera = Camera::getInstance();
    sf::RenderWindow& window = camera.getWindow();

    while (window.isOpen()) {
        // 1. TICK THE STOPWATCH
        // This calculates deltaTime, and sleeps if the frame finished too fast (frame rate capping)
        stopwatch.tick();

        // 2. INPUT HANDLING
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sm.empty()) {
                window.close();
                return;
            }
            camera.handleEvent(event);
            sm.handleInput(event);
        }

        // 3. UPDATE LOGIC
        // You would typically call an update function here, passing the deltaTime
        // sm.update(stopwatch.getDeltaTime());
        // camera.update(stopwatch.getDeltaTime());

        window.clear(sf::Color::Black);
        camera.applyView();
        sm.drawScreen();
        window.display();
    }
}