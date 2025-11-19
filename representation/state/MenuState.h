
#ifndef PACMAN_MENUSTATE_H
#define PACMAN_MENUSTATE_H
#include "AbstractState.h"

class MenuState final : public AbstractState {
private:
    sf::Font m_font;
    sf::Text m_pacmanText;
    sf::Text m_playText;
public:
    MenuState();
    void drawScreen() override;
    std::unique_ptr<AbstractState> handleInput(const sf::Event&, unsigned int& amountOfPops) override;
};

#endif // PACMAN_MENUSTATE_H
