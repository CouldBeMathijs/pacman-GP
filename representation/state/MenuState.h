#ifndef PACMAN_MENUSTATE_H
#define PACMAN_MENUSTATE_H
#include "AbstractState.h"
#include "Direction.h"

class MenuState final : public AbstractState {
private:
    sf::Text m_pacmanText;
    sf::Text m_playText;
public:
    MenuState();
    void update(Direction d) override;
    void handleInput(const sf::Event&) override;
};

#endif // PACMAN_MENUSTATE_H
