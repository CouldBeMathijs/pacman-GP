
#ifndef PACMAN_MENUSTATE_H
#define PACMAN_MENUSTATE_H
#include "State.h"

class MenuState final : public State {
private:
    sf::Font m_font;
    sf::Text m_pacmanText;
    sf::Text m_playText;
public:
    MenuState();
    void drawScreen(sf::RenderWindow&) override;
    std::unique_ptr<State> handleInput(const sf::Event&, unsigned int& amountOfPops) override;
};

#endif // PACMAN_MENUSTATE_H
