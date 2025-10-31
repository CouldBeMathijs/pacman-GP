#include "Game.h"

#include "Stopwatch.h"
#include "World.h"
#include <SFML/Graphics.hpp>
void Game::run() {
    sf::RenderWindow window(
        sf::VideoMode(800, 600),
        "Pacman AP",
        sf::Style::Close | sf::Style::Resize
    );
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        // window.draw(myShape);

        window.display();
    }
}