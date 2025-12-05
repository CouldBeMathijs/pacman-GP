#include "GhostView.h"

BlueGhostView::BlueGhostView(std::shared_ptr<IEntityModel> e)
    : IDirectionalEntityView(Assets::getSpriteInfo(Assets::GhostBlueBase), std::move(e), 2) {}

PinkGhostView::PinkGhostView(std::shared_ptr<IEntityModel> e)
    : IDirectionalEntityView(Assets::getSpriteInfo(Assets::GhostPinkBase), std::move(e), 2) {}

OrangeGhostView::OrangeGhostView(std::shared_ptr<IEntityModel> e)
    : IDirectionalEntityView(Assets::getSpriteInfo(Assets::GhostOrangeBase), std::move(e), 2) {}

RedGhostView::RedGhostView(std::shared_ptr<IEntityModel> e)
    : IDirectionalEntityView(Assets::getSpriteInfo(Assets::GhostRedBase), std::move(e), 2) {}

