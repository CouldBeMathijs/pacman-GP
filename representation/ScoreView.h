#ifndef PACMAN_SCOREVIEW_H
#define PACMAN_SCOREVIEW_H
#include "Observer.h"

#include <SFML/Graphics.hpp>

class ScoreView final : public Observer {
private:
    sf::Text m_scoreText;

public:
    ScoreView();
    void update() override;
};

#endif // PACMAN_SCOREVIEW_H
