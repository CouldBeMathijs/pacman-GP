
#include "LevelState.h"

#include "PausedState.h"

#include <iostream>
LevelState::LevelState() {
}

void LevelState::drawScreen(sf::RenderWindow&) {}

std::unique_ptr<AbstractState> LevelState::handleInput(const sf::Event& event, unsigned int& amountOfPops) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        return std::make_unique<PausedState>();
    }
    return nullptr;
}
