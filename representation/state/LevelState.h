
#ifndef PACMAN_LEVELSTATE_H
#define PACMAN_LEVELSTATE_H
#include "AbstractState.h"
#include "World.h"

class LevelState final : public AbstractState {
private:
    World world;
public:
    LevelState();
    void drawScreen(sf::RenderWindow&) override;
    std::unique_ptr<AbstractState> handleInput(const sf::Event&, unsigned int& amountOfPops) override;
};

#endif // PACMAN_LEVELSTATE_H
