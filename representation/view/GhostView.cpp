#include "GhostView.h"

IGhostView::IGhostView(Assets::TextureLocation t, std::shared_ptr<IEntityModel> e) : IDirectionalEntityView(t, std::move(e), 2) {}

BlueGhostView::BlueGhostView(std::shared_ptr<IEntityModel> e)
    : IGhostView(Assets::getSpriteInfo(Assets::GhostBlueBase), std::move(e)) {}

PinkGhostView::PinkGhostView(std::shared_ptr<IEntityModel> e)
    : IGhostView(Assets::getSpriteInfo(Assets::GhostPinkBase), std::move(e)) {}

OrangeGhostView::OrangeGhostView(std::shared_ptr<IEntityModel> e)
    : IGhostView(Assets::getSpriteInfo(Assets::GhostOrangeBase), std::move(e)) {}

RedGhostView::RedGhostView(std::shared_ptr<IEntityModel> e)
    : IGhostView(Assets::getSpriteInfo(Assets::GhostRedBase), std::move(e)) {}
