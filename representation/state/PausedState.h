
#ifndef PACMAN_PAUSEDSTATE_H
#define PACMAN_PAUSEDSTATE_H
#include "AbstractState.h"

class PausedState final : public AbstractState {
private:
    sf::Font m_font;
    sf::Text m_pacmanText;
    sf::Text m_playText;
public:
    PausedState();
    void drawScreen(sf::RenderWindow&) override;
    std::unique_ptr<AbstractState> handleInput(const sf::Event&, unsigned int& amountOfPops) override;
};


#endif // PACMAN_PAUSEDSTATE_H
