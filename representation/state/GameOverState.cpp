#include "GameOverState.h"

void GameOverState::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            requestedPops = 1;
        }
    }
}
