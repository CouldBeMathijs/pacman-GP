#include "Spritemap.h"

namespace {
sf::Texture texture;

bool initialized = false;

using namespace Spritemap;

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