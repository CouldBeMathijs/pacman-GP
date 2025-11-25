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
    WallBase,
    PacmanDeathBase,
    GhostDeathBase,
    Count
};

constexpr size_t to_underlying(const SpriteDefinition e) noexcept {
    return static_cast<size_t>(e);
}

const std::array<SpriteInfo, to_underlying(Count)> spriteDefinitions = {
    SpriteInfo{414, 266, 10, 10},  // SpriteDefinition::Coin
    SpriteInfo{594, -4, 50, 50},   // SpriteDefinition::Fruit
    SpriteInfo{744, -4, 50, 50},   // SpriteDefinition::GhostBlue
    SpriteInfo{794, -4, 50, 50},   // SpriteDefinition::GhostOrange
    SpriteInfo{-6,  547,50, 50},   // SpriteDefinition::GhostPanic
    SpriteInfo{694, -4, 50, 50},   // SpriteDefinition::GhostPink
    SpriteInfo{644, -4, 50, 50},   // SpriteDefinition::GhostRed
    SpriteInfo{844, -4, 50, 50},   // SpriteDefinition::Pacman
    SpriteInfo{644, 395, 50, 50},   // SpriteDefinition::Wall
    SpriteInfo{344, -4, 50, 50},   // SpriteDefinition::PacmanDeath
    SpriteInfo{244, -4, 50, 50},   // SpriteDefinition::GhostDeath
};

SpriteInfo getSpriteInfo(SpriteDefinition);

const sf::Texture& getTexture();

void initialize();
}

#endif // PACMAN_SPRITEMAP_H