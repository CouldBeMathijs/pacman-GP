#ifndef PACMAN_SPRITEMAP_H
#define PACMAN_SPRITEMAP_H

#include <string>
#include <optional>
#include <iostream>
#include <SFML/Graphics.hpp> // Include SFML Graphics header

namespace Spritemap {
using SpriteInfo = sf::IntRect;

// Public functions, which act like the old static methods
std::optional<SpriteInfo> getSpriteInfo(const std::string& name);
const sf::Texture& getTexture();

void initialize();
}

#endif // PACMAN_SPRITEMAP_H