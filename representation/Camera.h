#ifndef PACMAN_CAMERA_H
#define PACMAN_CAMERA_H

#include <SFML/Graphics.hpp>



class Camera {
private:
    sf::RenderWindow window;
    sf::View view;
    sf::FloatRect currentViewport;

    Camera(sf::VideoMode mode, const sf::String& title, sf::Uint32 style);

public:
    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;
    static Camera& getInstance();
    void handleEvent(const sf::Event& event);

    sf::RenderWindow& getWindow();
    const sf::FloatRect& getViewport() const;

    void applyView();
};

#endif // PACMAN_CAMERA_H
