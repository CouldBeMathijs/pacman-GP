
#ifndef PACMAN_LEVELSTATE_H
#define PACMAN_LEVELSTATE_H
#include "../Camera.h"
#include "../ConcreteEntityFactory.h"
#include "AbstractState.h"
#include "World.h"

class LevelState final : public AbstractState {
private:
    World world;
    std::shared_ptr<ConcreteEntityFactory> factory;
public:
    LevelState();
    void drawScreen() override;
    std::unique_ptr<AbstractState> handleInput(const sf::Event&, unsigned int& amountOfPops) override;
};

#endif // PACMAN_LEVELSTATE_H
