#include "EntityView.h"

#include <utility>

#include "Camera.h"
#include "Position.h"
#include "SfmlConstants.h"
#include "Stopwatch.h"

#include <memory>

EntityView::EntityView(Spritemap::SpriteInfo m, std::shared_ptr<EntityModel> n)
    : coupledEntity(std::move(n)), currentSprite(m) {}

void EntityView::update() {
    auto& camera = Camera::getInstance();
    auto& window = camera.getWindow();
    animate();
    const Position p =
        coupledEntity->getPosition().rescale({-1, -LogicConstants::REVERSE_TARGET_ASPECT_RATIO},
            {1, LogicConstants::REVERSE_TARGET_ASPECT_RATIO}, {0, 0},
            {SfmlConstants::VIEW_WIDTH, SfmlConstants::VIEW_HEIGHT});

    sf::Sprite sprite(Spritemap::getTexture(), currentSprite);

    constexpr float targetWidth = static_cast<float>(SfmlConstants::VIEW_WIDTH) / LogicConstants::AMOUNT_OF_ENTITIES_WIDTH;
    constexpr float targetHeight = static_cast<float>(SfmlConstants::VIEW_HEIGHT) / LogicConstants::AMOUNT_OF_ENTITIES_HEIGHT;

    const auto currentWidth = static_cast<float>(currentSprite.width);
    const auto currentHeight = static_cast<float>(currentSprite.height);

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
    currentSprite.top = topBase + 50 *
        ( getCurrentTextureOffset() + amountOfTextures * static_cast<unsigned int>(getCoupledEntity()->getDirection()));
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
        currentSprite.top += 50;
    } else {
        currentTextureOffset -= 1;
        currentSprite.top -= 50;
    }
}

unsigned int EntityView::getCurrentTextureOffset() const { return currentTextureOffset; }

std::shared_ptr<EntityModel> EntityView::getCoupledEntity() { return coupledEntity; }

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
