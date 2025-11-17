#include "Spritemap.h"

namespace {
const std::map<std::string, Spritemap::SpriteInfo> spriteDefinitions = {
    {"CoinBase", {410, 358, 6,6 }},
    {"FruitBase", {601, 3, 35, 35}},
    {"GhostBlue", {101, 4, 35, 35}},
    {"GhostOrange", {151, 4, 35, 35}},
    {"GhostPanic", {1, 554, 35, 35 }},
    {"GhostPink", {51, 4, 35, 35}},
    {"GhostRed", {1, 4, 35, 35}},
    {"PacmanBase", {853, 5, 33, 33}},
};



sf::Texture texture;

bool initialized = false;
} // namespace

enum spriteDefinition {
    CoinBase,
    FruitBase,
    GhostBlueBase,
    GhostOrangeBase,
    GhostPanicBase,
    GhostPinkBase,
    GhostRedBase,
    PacmanBase,
};

void Spritemap::initialize() {
    if (initialized) {
        return;
    }

    if (!texture.loadFromFile("assets/spritemap.png")) {
        throw std::invalid_argument("The spritemap is not at the expected location of \"assets/spritemap.png\"");
    }
    initialized = true;
}

std::optional<Spritemap::SpriteInfo> Spritemap::getSpriteInfo(const std::string& name) {
    if (const auto it = spriteDefinitions.find(name); it != spriteDefinitions.end()) {
        return it->second;
    }
    return std::nullopt;
}

const sf::Texture& Spritemap::getTexture() {
    initialize();
    return texture;
}