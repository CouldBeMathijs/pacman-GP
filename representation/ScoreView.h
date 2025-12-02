#ifndef PACMAN_SCOREVIEW_H
#define PACMAN_SCOREVIEW_H
#include "Observer.h"

#include <SFML/Graphics.hpp>

/**
 * @brief Observer for displaying the current score on the screen
 */
class ScoreView final : public Observer {
    sf::Text m_scoreText;

public:
    ScoreView();
    void update() override;
};

#endif // PACMAN_SCOREVIEW_H
