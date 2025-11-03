#ifndef PACMAN_STATE_H
#define PACMAN_STATE_H

#include "World.h"
#include <SFML/Graphics.hpp>
#include <memory>

class State {
public:
    virtual ~State() = default;
    virtual void drawScreen(sf::RenderWindow&) = 0;
protected:
    State() = default;
};

class MenuState final : public State {
private:
    sf::Font m_font;
    sf::Text m_pacmanText;
    sf::Text m_playText;
public:
    void drawScreen(sf::RenderWindow&) override;
    MenuState();
};
class LevelState final : public State {
    void drawScreen(sf::RenderWindow&) override;
private:
    World world;
};
class PausedState final : public State {
    void drawScreen(sf::RenderWindow&) override;
};
class VictoryState final : public State {
    void drawScreen(sf::RenderWindow&) override;
};

#endif // PACMAN_STATE_H
