
#include "LevelState.h"

#include "PausedState.h"

#include <iostream>
LevelState::LevelState() : factory(std::make_shared<ConcreteEntityFactory>()) {
    world = WorldCreator::createWorldFromFile("./assets/worldmap", factory);
}

void LevelState::drawScreen(sf::RenderWindow& window) {
    for (const auto& e : world.getEntities()) {
        Position p = e->getPosition().rescale({-1,-1},{1,1},{0,0},{static_cast<double>(window.getSize().x), static_cast<double>(window.getSize().y)});
    }
}

std::unique_ptr<AbstractState> LevelState::handleInput(const sf::Event& event, unsigned int& amountOfPops) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        return std::make_unique<PausedState>();
    }
    return nullptr;
}
