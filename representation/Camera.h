
#ifndef PACMAN_CAMERA_H
#define PACMAN_CAMERA_H

#include <SFML/Graphics.hpp>

class Camera {
private:
    sf::RenderWindow window;
    sf::View view;

    Camera(sf::VideoMode mode, const sf::String& title, sf::Uint32 style);

public:
    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;
    static Camera& getInstance();
    void handleEvent(const sf::Event& event);

    sf::RenderWindow& getWindow();

    void applyView();
};

#endif // PACMAN_CAMERA_H
