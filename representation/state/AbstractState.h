#ifndef PACMAN_STATE_H
#define PACMAN_STATE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Direction.h"

class AbstractState {
public:
    virtual ~AbstractState() = default;
    virtual void update(Direction) = 0;
    virtual std::unique_ptr<AbstractState> handleInput(const sf::Event&, unsigned int& amountOfPops) = 0;
protected:
    AbstractState() = default;
};

#endif // PACMAN_STATE_H
