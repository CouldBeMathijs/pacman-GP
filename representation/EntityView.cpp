#include "EntityView.h"

#include <utility>

#include "Camera.h"
#include "Position.h"

EntityView::EntityView(Spritemap::SpriteInfo m, std::shared_ptr<EntityModel> n ) : base(m), coupledEntity(std::move(n)) {}
void EntityView::update() {
    auto& camera = Camera::getInstance();
    auto& window = camera.getWindow();

    Position p = coupledEntity->getPosition().rescale({-1,-1},{1,1},{0,0},{static_cast<double>(window.getSize().x), static_cast<double>(window.getSize().y)});

    sf::Sprite sprite(Spritemap::getTexture(), base);

    sprite.setPosition(static_cast<float>(p.x), static_cast<float>(p.y));

    window.draw(sprite);
}

DirectionalEntityView::DirectionalEntityView(Spritemap::SpriteInfo m, std::shared_ptr<EntityModel> n, int amountOfTextures) :
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
    EntityView(Spritemap::getSpriteInfo(Spritemap::GhostBlueBase), std::move(e)) {}
