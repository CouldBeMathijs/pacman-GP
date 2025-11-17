
#include "Spritemap.h"
Spritemap& Spritemap::getInstance() {
        static Spritemap instance;
        return instance;
}
std::optional<SpriteInfo> Spritemap::getSpriteInfo(const std::string& name) const {

}
const sf::Texture& Spritemap::getTexture() const {
    return texture;
}