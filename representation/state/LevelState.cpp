#include "LevelState.h"

#include "GameOverState.h"
#include "PausedState.h"

LevelState::LevelState() : factory(std::make_shared<ConcreteEntityFactory>()) {
    world = WorldCreator::createWorldFromFile("./assets/worldmap", factory);
}

void LevelState::update(Direction d) {
    if (!world.isRunning()) {
        requestedPops = 1;
        requestedState = std::make_unique<GameOverState>();
    }
   world.update(d);
}

void LevelState::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        requestedState = std::make_unique<PausedState>();
    }
}
