
#include "LevelState.h"

#include <iostream>
LevelState::LevelState() {
    std::cout << "HI" << std::endl;
}

void LevelState::drawScreen(sf::RenderWindow&) {}

std::unique_ptr<State> LevelState::handleInput(const sf::Event&, unsigned int& amountOfPops) {
    return nullptr;
}
