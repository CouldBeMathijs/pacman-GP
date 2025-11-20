#include "EntityView.h"

#include <utility>

#include "Camera.h"
#include "GameConstants.h"
#include "Position.h"
#include <memory>


EntityView::EntityView(Spritemap::SpriteInfo m, std::shared_ptr<EntityModel> n)
    : base(m), coupledEntity(std::move(n))
{
}

void EntityView::update() {
    auto& camera = Camera::getInstance();
    auto& window = camera.getWindow();

    const Position p = coupledEntity->getPosition().rescale(
        {-1,-1},
        {1,1},
        {0,0},
        {Constants::VIEW_WIDTH, Constants::VIEW_HEIGHT}
    );

    sf::Sprite sprite(Spritemap::getTexture(), base);

    constexpr float targetWidth = static_cast<float>(Constants::VIEW_WIDTH) / Constants::AMOUNT_OF_ENTITIES_WIDTH;
    constexpr float targetHeight = static_cast<float>(Constants::VIEW_HEIGHT) / Constants::AMOUNT_OF_ENTITIES_HEIGHT;

    const auto currentWidth = static_cast<float>(base.width);
    const auto currentHeight = static_cast<float>(base.height);

    const float scaleX = targetWidth / currentWidth;
    const float scaleY = targetHeight / currentHeight;

    sprite.setScale(scaleX, scaleY);

    sprite.setPosition(static_cast<float>(p.x), static_cast<float>(p.y));

    window.draw(sprite);
}

DirectionalEntityView::DirectionalEntityView(Spritemap::SpriteInfo m, std::shared_ptr<EntityModel> n,
                                             const int amountOfTextures) :
    EntityView(m,std::move(n)), amountOfTextures(amountOfTextures) {}

CoinView::CoinView(std::shared_ptr<EntityModel> e) :
    EntityView(Spritemap::getSpriteInfo(Spritemap::CoinBase), std::move(e)) {}

FruitView::FruitView(std::shared_ptr<EntityModel> e) :
    EntityView(Spritemap::getSpriteInfo(Spritemap::FruitBase), std::move(e)) {}

GhostView::GhostView(std::shared_ptr<EntityModel> e) :
    DirectionalEntityView(Spritemap::getSpriteInfo(Spritemap::GhostPinkBase),std::move(e),2) {}

PacmanView::PacmanView(std::shared_ptr<EntityModel> e) :
    DirectionalEntityView(Spritemap::getSpriteInfo(Spritemap::PacmanBase),std::move(e), 3) {}

WallView::WallView(std::shared_ptr<EntityModel> e) :
    EntityView(Spritemap::getSpriteInfo(Spritemap::WallBase), std::move(e)) {}
