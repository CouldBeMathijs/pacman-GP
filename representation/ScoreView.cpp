
#include "ScoreView.h"

#include "AssetManager.h"
#include "Camera.h"
#include "ScoreKeeper.h"
#include "SfmlConstants.h"

ScoreView::ScoreView() {
    m_scoreText.setFont(Assets::getDefaultFont());
    m_scoreText.setString("Score: 0");
    m_scoreText.setCharacterSize(50);
    m_scoreText.setFillColor(sf::Color::Yellow);

    const sf::FloatRect bounds = m_scoreText.getLocalBounds();
    m_scoreText.setOrigin(bounds.left, bounds.top);
}

void ScoreView::update() {
    auto& window = Camera::getInstance().getWindow();

    const unsigned int currentScore = ScoreKeeper::getInstance().getScore();
    const std::string scoreString = "Score: " + std::to_string(currentScore);
    m_scoreText.setString(scoreString);

    auto& viewport = Camera::getInstance().getViewport();

    const sf::FloatRect bounds = m_scoreText.getLocalBounds();

    m_scoreText.setOrigin(bounds.left, bounds.top);

    constexpr float margin = 20.f;

    const float posX = - viewport.getSize().x + margin;

    const float posY = SfmlConstants::VIEW_HEIGHT - bounds.height - margin;

    m_scoreText.setPosition(posX, posY);

    window.draw(m_scoreText);
}