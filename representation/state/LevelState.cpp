
#include "LevelState.h"

#include "PausedState.h"

LevelState::LevelState() : factory(std::make_shared<ConcreteEntityFactory>()) {
    world = WorldCreator::createWorldFromFile("./assets/worldmap", factory);
}

void LevelState::update(Direction d) {
   world.update(d);
}

std::unique_ptr<AbstractState> LevelState::handleInput(const sf::Event& event, unsigned int& amountOfPops) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        return std::make_unique<PausedState>();
    }
    return nullptr;
}
