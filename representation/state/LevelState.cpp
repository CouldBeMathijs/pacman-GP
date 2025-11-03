
#include "LevelState.h"

#include <iostream>
LevelState::LevelState() {
}

void LevelState::drawScreen(sf::RenderWindow&) {}

std::unique_ptr<State> LevelState::handleInput(const sf::Event& event, unsigned int& amountOfPops) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        amountOfPops = 1;
    }
    return nullptr;
}
