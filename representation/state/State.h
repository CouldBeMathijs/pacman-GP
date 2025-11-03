#ifndef PACMAN_STATE_H
#define PACMAN_STATE_H

#include <SFML/Graphics.hpp>
#include <memory>

class State {
public:
    virtual ~State() = default;
    virtual void drawScreen(sf::RenderWindow&) = 0;
    virtual std::unique_ptr<State> handleInput(const sf::Event&, unsigned int& amountOfPops) = 0;
protected:
    State() = default;
};




#endif // PACMAN_STATE_H
