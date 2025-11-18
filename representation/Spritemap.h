#ifndef PACMAN_SPRITEMAP_H
#define PACMAN_SPRITEMAP_H

#include <array>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace Spritemap {
using SpriteInfo = sf::IntRect;

enum SpriteDefinition {
    CoinBase,
    FruitBase,
    GhostBlueBase,
    GhostOrangeBase,
    GhostPanicBase,
    GhostPinkBase,
    GhostRedBase,
    PacmanBase,
    Count
};

constexpr size_t to_underlying(const SpriteDefinition e) noexcept {
    return static_cast<size_t>(e);
}

const std::array<SpriteInfo, to_underlying(Count)> spriteDefinitions = {
    SpriteInfo{410, 358, 6, 6},    // SpriteDefinition::Coin
    SpriteInfo{601, 3, 35, 35},    // SpriteDefinition::Fruit
    SpriteInfo{101, 4, 35, 35},    // SpriteDefinition::GhostBlue
    SpriteInfo{151, 4, 35, 35},    // SpriteDefinition::GhostOrange
    SpriteInfo{1, 554,35, 35},     // SpriteDefinition::GhostPanic
    SpriteInfo{51, 4, 35, 35},     // SpriteDefinition::GhostPink
    SpriteInfo{1, 4, 35, 35},      // SpriteDefinition::GhostRed
    SpriteInfo{853, 5, 33, 33}     // SpriteDefinition::Pacman
};

SpriteInfo getSpriteInfo(SpriteDefinition);

const sf::Texture& getTexture();

void initialize();
}

#endif // PACMAN_SPRITEMAP_H