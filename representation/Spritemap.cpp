#include "Spritemap.h"

namespace {
sf::Texture texture;

bool initialized = false;

using namespace Spritemap;
const std::array spriteDefinitions = {

    SpriteInfo{410, 358, 6, 6},    // SpriteDefinition::Coin
    SpriteInfo{601, 3, 35, 35},    // SpriteDefinition::Fruit
    SpriteInfo{101, 4, 35, 35},    // SpriteDefinition::GhostBlue
    SpriteInfo{151, 4, 35, 35},    // SpriteDefinition::GhostOrange
    SpriteInfo{1, 554,35, 35},     // SpriteDefinition::GhostPanic
    SpriteInfo{51, 4, 35, 35},     // SpriteDefinition::GhostPink
    SpriteInfo{1, 4, 35, 35},      // SpriteDefinition::GhostRed
    SpriteInfo{853, 5, 33, 33}     // SpriteDefinition::Pacman
};
} // namespace



void Spritemap::initialize() {
    if (initialized) {
        return;
    }

    if (!texture.loadFromFile("assets/spritemap.png")) {
        throw std::invalid_argument("The spritemap is not at the expected location of \"assets/spritemap.png\"");
    }
    initialized = true;
}

SpriteInfo Spritemap::getSpriteInfo(SpriteDefinition d) {
    return spriteDefinitions[to_underlying(d)];
}

const sf::Texture& Spritemap::getTexture() {
    initialize();
    return texture;
}