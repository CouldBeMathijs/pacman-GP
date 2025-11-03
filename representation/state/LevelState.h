
#ifndef PACMAN_LEVELSTATE_H
#define PACMAN_LEVELSTATE_H
#include "State.h"
#include "World.h"

class LevelState final : public State {
private:
    World world;
public:
    LevelState();
    void drawScreen(sf::RenderWindow&) override;
    std::unique_ptr<State> handleInput(const sf::Event&, unsigned int& amountOfPops) override;
};


#endif // PACMAN_LEVELSTATE_H
