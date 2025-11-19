
#include "Camera.h"
#include "GameConstants.h"

using namespace Constants;
void resizeView(const sf::RenderWindow& window, sf::View& view, sf::FloatRect& currentViewport)
{
    sf::Vector2u windowSize = window.getSize();
    float windowAspectRatio = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);

    sf::FloatRect viewport;

    if (windowAspectRatio > TARGET_ASPECT_RATIO) {
        float width = TARGET_ASPECT_RATIO / windowAspectRatio;
        float x = (1.0f - width) / 2.0f; // Center the viewport horizontally
        viewport = sf::FloatRect(x, 0.0f, width, 1.0f);
    } else {
        float height = windowAspectRatio / TARGET_ASPECT_RATIO;
        float y = (1.0f - height) / 2.0f; // Center the viewport vertically
        viewport = sf::FloatRect(0.0f, y, 1.0f, height);
    }

    view.setViewport(viewport);

    currentViewport = viewport;

    view.setSize(VIEW_WIDTH, VIEW_HEIGHT);
}

Camera& Camera::getInstance() {
    static Camera instance(sf::VideoMode(static_cast<unsigned int>(VIEW_WIDTH), static_cast<unsigned int>(VIEW_HEIGHT)),
                           "Pacman GP", sf::Style::Close | sf::Style::Resize);
    return instance;
}

Camera::Camera(sf::VideoMode mode, const sf::String& title, sf::Uint32 style)
    : window(mode, title, style),
      view(sf::FloatRect(0.f, 0.f, VIEW_WIDTH, VIEW_HEIGHT))
{
    resizeView(window, view, currentViewport);
    window.setView(view);
}

void Camera::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::Resized) {
        resizeView(window, view, currentViewport);
        window.setView(view);
    }
}

sf::RenderWindow& Camera::getWindow() {
    return window;
}

const sf::FloatRect& Camera::getViewport() const { return currentViewport; }

void Camera::applyView() {
    window.setView(view);
}