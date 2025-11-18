
#include "Camera.h"
#include <iostream>

void resizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
    view.setSize(800.f * aspectRatio, 600.f); // Base size is 800x600
}

Camera::Camera(sf::VideoMode mode, const sf::String& title, sf::Uint32 style)
    : window(mode, title, style),
      view(sf::FloatRect(0.f, 0.f, mode.width, mode.height))
{
    window.setView(view);
}

Camera& Camera::getInstance() {
    static Camera instance(sf::VideoMode(800, 600), "Pacman GP", sf::Style::Close | sf::Style::Resize);
    return instance;
}

void Camera::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::Resized) {
        resizeView(window, view);
        window.setView(view);
    }
}

sf::RenderWindow& Camera::getWindow() {
    return window;
}

void Camera::applyView() {
    window.setView(view);
}