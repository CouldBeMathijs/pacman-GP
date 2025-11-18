#ifndef PACMAN_SPRITEMAP_H
#define PACMAN_SPRITEMAP_H

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
    PacmanBase
};

constexpr size_t to_underlying(const SpriteDefinition e) noexcept {
    return static_cast<size_t>(e);
}

SpriteInfo getSpriteInfo(SpriteDefinition);

const sf::Texture& getTexture();

void initialize();
}

#endif // PACMAN_SPRITEMAP_H