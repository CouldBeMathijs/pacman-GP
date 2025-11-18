
#include "LevelState.h"

#include "PausedState.h"

#include <iostream>
LevelState::LevelState() : factory(std::make_shared<ConcreteEntityFactory>()) {
    world = WorldCreator::createWorldFromFile("./assets/worldmap", factory);
}

void LevelState::drawScreen(sf::RenderWindow& window) {
   world.update();
}

std::unique_ptr<AbstractState> LevelState::handleInput(const sf::Event& event, unsigned int& amountOfPops) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        return std::make_unique<PausedState>();
    }
    return nullptr;
}
