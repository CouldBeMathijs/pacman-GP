#include "EntityView.h"

#include <utility>

#include "Camera.h"
#include "GameConstants.h"
#include "Position.h"
#include "Stopwatch.h"

#include <memory>

EntityView::EntityView(Spritemap::SpriteInfo m, std::shared_ptr<EntityModel> n)
    : coupledEntity(std::move(n)), base(m) {}

void EntityView::update() {
    auto& camera = Camera::getInstance();
    auto& window = camera.getWindow();
    animate();
    const Position p =
        coupledEntity->getPosition().rescale({-1, -1}, {1, 1}, {0, 0}, {Constants::VIEW_WIDTH, Constants::VIEW_HEIGHT});

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
                                             const int amountOfTextures)
    : EntityView(m, std::move(n)) {
    this->amountOfTextures = amountOfTextures;
}

void DirectionalEntityView::update() {
    EntityView::update();
}

void EntityView::animate() {
    if (amountOfTextures <= 1) {
        return;
    }
    timeAccumulator += Stopwatch::getInstance().getDeltaTime();

    if (timeAccumulator < timePerFrame) {
        return;
    }

    timeAccumulator -= timePerFrame;

    if (animationCycleMovingUp && currentTextureOffset == amountOfTextures - 1) {
        animationCycleMovingUp = false;
    } else if (!animationCycleMovingUp && currentTextureOffset == 0) {
        animationCycleMovingUp = true;
    }

    if (animationCycleMovingUp) {
        currentTextureOffset += 1;
        base.top += 50;
    } else {
        currentTextureOffset -= 1;
        base.top -= 50;
    }
}

CoinView::CoinView(std::shared_ptr<EntityModel> e)
    : EntityView(Spritemap::getSpriteInfo(Spritemap::CoinBase), std::move(e)) {}

FruitView::FruitView(std::shared_ptr<EntityModel> e)
    : EntityView(Spritemap::getSpriteInfo(Spritemap::FruitBase), std::move(e)) {}

BlueGhostView::BlueGhostView(std::shared_ptr<EntityModel> e)
    : DirectionalEntityView(Spritemap::getSpriteInfo(Spritemap::GhostBlueBase), std::move(e), 2) {}

PinkGhostView::PinkGhostView(std::shared_ptr<EntityModel> e)
    : DirectionalEntityView(Spritemap::getSpriteInfo(Spritemap::GhostPinkBase), std::move(e), 2) {}

OrangeGhostView::OrangeGhostView(std::shared_ptr<EntityModel> e)
    : DirectionalEntityView(Spritemap::getSpriteInfo(Spritemap::GhostOrangeBase), std::move(e), 2) {}

RedGhostView::RedGhostView(std::shared_ptr<EntityModel> e)
    : DirectionalEntityView(Spritemap::getSpriteInfo(Spritemap::GhostRedBase), std::move(e), 2) {}

PacmanView::PacmanView(std::shared_ptr<EntityModel> e)
    : DirectionalEntityView(Spritemap::getSpriteInfo(Spritemap::PacmanBase), std::move(e), 3) {}

WallView::WallView(std::shared_ptr<EntityModel> e)
    : EntityView(Spritemap::getSpriteInfo(Spritemap::WallBase), std::move(e)) {}
