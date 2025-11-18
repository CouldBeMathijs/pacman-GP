#include "EntityView.h"

EntityView::EntityView(const Spritemap::SpriteInfo m) : base(m) {}

void EntityView::update() {}

DirectionalEntityView::DirectionalEntityView(Spritemap::SpriteInfo m, unsigned int amountOfTextures) :  EntityView(m), amountOfTextures(amountOfTextures) {}
CoinView::CoinView() :
    EntityView(Spritemap::getSpriteInfo(Spritemap::CoinBase)) {}

FruitView::FruitView() :
    EntityView(Spritemap::getSpriteInfo(Spritemap::FruitBase)) {}

GhostView::GhostView() :  DirectionalEntityView(Spritemap::getSpriteInfo(Spritemap::GhostPinkBase),2) {}

PacmanView::PacmanView() : DirectionalEntityView(Spritemap::getSpriteInfo(Spritemap::PacmanBase),3) {}

WallView::WallView() :
    EntityView(Spritemap::getSpriteInfo(Spritemap::GhostBlueBase)) {}
