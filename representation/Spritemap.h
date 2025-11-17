#ifndef PACMAN_SPRITEMAP_H
#define PACMAN_SPRITEMAP_H

#include <string>
#include <map>
#include <optional>
#include <iostream>
#include <SFML/Graphics.hpp> // Include SFML Graphics header

// 1. Define a structure to hold the SFML texture rectangle (sub-image coordinates).
// We use sf::IntRect directly, which is ideal for SFML sprites.
using SpriteInfo = sf::IntRect;

class Spritemap {
private:
    // 2. Private storage for the entire spritemap.
    std::map<std::string, SpriteInfo> spriteDefinitions;

    // 3. Private storage for the main SFML Texture, loaded from the PNG file.
    sf::Texture texture;
    Spritemap();

public:
    // Deleted copy/assignment constructors to enforce Singleton
    Spritemap(const Spritemap&) = delete;
    Spritemap& operator=(const Spritemap&) = delete;

    // Access method for the Singleton instance
    static Spritemap& getInstance();

    // 4. Public function to retrieve a specific piece of the spritemap (the sub-rectangle).
    std::optional<SpriteInfo> getSpriteInfo(const std::string& name) const;

    // 5. NEW: Function to return a reference to the loaded texture.
    const sf::Texture& getTexture() const;

    // Example of a utility function (optional, but useful)
    void printAllSprites() const;
};

#endif // PACMAN_SPRITEMAP_H