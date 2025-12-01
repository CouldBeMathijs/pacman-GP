#ifndef PACMAN_SPRITEMAP_H
#define PACMAN_SPRITEMAP_H

#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

namespace Assets {
using TextureLocation = sf::IntRect;

enum SpriteDefinition {
    CoinBase,
    FruitBase,
    GhostBlueBase,
    GhostOrangeBase,
    GhostPanicBase,
    GhostPinkBase,
    GhostRedBase,
    PacmanBase,
    WallBase,
    PacmanDeathBase,
    GhostDeathBase,
    Count
};

constexpr size_t to_underlying(const SpriteDefinition e) noexcept { return static_cast<size_t>(e); }

const std::array<TextureLocation, to_underlying(Count)> k_spriteDefinitions = {
    TextureLocation{414, 266, 10, 10}, // SpriteDefinition::Coin
    TextureLocation{594, -4, 50, 50},  // SpriteDefinition::Fruit
    TextureLocation{744, -4, 50, 50},  // SpriteDefinition::GhostBlue
    TextureLocation{794, -4, 50, 50},  // SpriteDefinition::GhostOrange
    TextureLocation{-6, 547, 50, 50},  // SpriteDefinition::GhostPanic
    TextureLocation{694, -4, 50, 50},  // SpriteDefinition::GhostPink
    TextureLocation{644, -4, 50, 50},  // SpriteDefinition::GhostRed
    TextureLocation{844, -4, 50, 50},  // SpriteDefinition::Pacman
    TextureLocation{644, 395, 50, 50}, // SpriteDefinition::Wall
    TextureLocation{344, -4, 50, 50},  // SpriteDefinition::PacmanDeath
    TextureLocation{244, -4, 50, 50},  // SpriteDefinition::GhostDeath
};

TextureLocation getSpriteInfo(SpriteDefinition);

const sf::Texture& getTexture();
const sf::Font& getDefaultFont();

void initialize();
} // namespace Assets

#endif // PACMAN_SPRITEMAP_H