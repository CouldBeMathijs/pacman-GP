
#ifndef PACMAN_CAMERA_H
#define PACMAN_CAMERA_H

#include <SFML/Graphics.hpp>

class Camera {
private:
    sf::RenderWindow window;
    sf::View view; // Add an sf::View to handle resizing and camera movement

public:
    // Constructor to create the window
    Camera(sf::VideoMode mode, const sf::String& title, sf::Uint32 style);

    // New: Handles events related to the window/view (like resizing)
    void handleEvent(const sf::Event& event);

    // Accessor for the window
    sf::RenderWindow& getWindow();

    // Optional: Method to apply the current view to the window
    void applyView();
};

#endif // PACMAN_CAMERA_H
