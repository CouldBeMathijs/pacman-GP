#include "Camera.h"
#include "SfmlConstants.h"


void resizeView(const sf::RenderWindow& window, sf::View& view, sf::FloatRect& currentViewport)
{
    sf::Vector2u windowSize = window.getSize();
    float windowAspectRatio = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);

    sf::FloatRect viewport;

    if (windowAspectRatio > LogicConstants::TARGET_ASPECT_RATIO) {
        const float width = LogicConstants::TARGET_ASPECT_RATIO / windowAspectRatio;
        const float x = (1.0f - width) / 2.0f; // Center the viewport horizontally
        viewport = sf::FloatRect(x, 0.0f, width, 1.0f);
    } else {
        const float height = windowAspectRatio / LogicConstants::TARGET_ASPECT_RATIO;
        const float y = (1.0f - height) / 2.0f; // Center the viewport vertically
        viewport = sf::FloatRect(0.0f, y, 1.0f, height);
    }

    view.setViewport(viewport);

    currentViewport = viewport;

    view.setSize(SfmlConstants::VIEW_WIDTH, SfmlConstants::VIEW_HEIGHT);
}

Camera& Camera::getInstance() {
    static Camera instance(sf::VideoMode(static_cast<unsigned int>(SfmlConstants::VIEW_WIDTH), static_cast<unsigned int>(SfmlConstants::VIEW_HEIGHT)),
                           "Pacman GP", sf::Style::Close | sf::Style::Resize);
    return instance;
}

Camera::Camera(const sf::VideoMode mode, const sf::String& title, const sf::Uint32 style)
    : window(mode, title, style),
      view(sf::FloatRect(0.f, 0.f, SfmlConstants::VIEW_WIDTH, SfmlConstants::VIEW_HEIGHT))
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