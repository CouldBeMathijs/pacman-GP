#include "AssetManager.h"

namespace {
sf::Texture k_texture;
sf::Font k_font;

bool initialized = false;

using namespace Assets;

} // namespace

void Assets::initialize() {
    if (initialized) {
        return;
    }

    if (!k_texture.loadFromFile("assets/spritemap.png")) {
        throw std::invalid_argument("The spritemap is not at the expected location of \"assets/spritemap.png\"");
    }

    if (!k_font.loadFromFile("./assets/BoldPixels/BoldPixels.ttf")) {
        throw std::runtime_error("Missing font BoldPixels");
    }

    initialized = true;
}

TextureLocation Assets::getSpriteInfo(SpriteDefinition d) { return k_spriteDefinitions[to_underlying(d)]; }

const sf::Texture& Assets::getTexture() {
    initialize();
    return k_texture;
}

const sf::Font& Assets::getDefaultFont() {
    initialize();
    return k_font;
}