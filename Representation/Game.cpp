#include "Game.h"

#include <SFML/Graphics.hpp>
Game::Game() :
    camera(sf::VideoMode(800, 600), "Pacman AP", sf::Style::Close | sf::Style::Resize)
{
}

void Game::run() {
    sf::RenderWindow& window = camera.getWindow();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            camera.handleEvent(event); // Example: for resizing/view changes
        }

        // update(deltaTime);

        window.clear(sf::Color::Black);

        camera.applyView();

        // window.draw(myShape);

        window.display();
    }
}