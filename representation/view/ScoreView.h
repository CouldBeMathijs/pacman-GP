#ifndef PACMAN_SCORE_VIEW_H
#define PACMAN_SCORE_VIEW_H
#include "IObserver.h"

#include <SFML/Graphics.hpp>

/**
 * @brief Observer for displaying the current score and amount of lives on the screen
 */
class ScoreView final : public IObserver {
    sf::Text m_livesText;
    sf::Text m_scoreText;

public:
    ScoreView();
    void update() override;
};

#endif