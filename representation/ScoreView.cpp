
#include "ScoreView.h"

#include "AssetManager.h"
#include "Camera.h"
#include "ScoreKeeper.h"


ScoreView::ScoreView() {
    // 2. Initialize the sf::Text object properties (Keep this in the constructor!)
    m_scoreText.setFont(Assets::getDefaultFont());
    m_scoreText.setString("Score: 0");
    m_scoreText.setCharacterSize(50);
    m_scoreText.setFillColor(sf::Color::Yellow);

    // Set origin once (It's safe to do it here, or in update if the string changes frequently)
    const sf::FloatRect bounds = m_scoreText.getLocalBounds();
    m_scoreText.setOrigin(bounds.left, bounds.top);

}

void ScoreView::update() {
    auto& window = Camera::getInstance().getWindow(); // Needed for drawing

    const unsigned int currentScore = ScoreKeeper::getInstance().getScore();
    const std::string scoreString = "Score: " + std::to_string(currentScore);
    m_scoreText.setString(scoreString);


    auto& viewport = Camera::getInstance().getViewport();

    const sf::FloatRect bounds = m_scoreText.getLocalBounds();

    // Ensure origin is set correctly once (or just leave it here for safety, though it's redundant if in the constructor)
    m_scoreText.setOrigin(bounds.left, bounds.top);

    // Position 20 pixels from the left and 20 pixels up from the bottom edge
    constexpr float margin = 15.f;

    // X Position: margin from the left edge
    constexpr float posX = margin;

    // Y Position: viewport height MINUS margin MINUS the text height
    const float posY = viewport.getSize().y + bounds.height;

    // Apply the newly calculated position
    m_scoreText.setPosition(posX, posY);

    // --- END NEW LOGIC ---

    // 4. Draw the score
    window.draw(m_scoreText);
}