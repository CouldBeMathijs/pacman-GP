#include "GhostView.h"

#include "entityType/Ghost.h"

IGhostView::IGhostView(const Assets::TextureLocation t, std::shared_ptr<IEntityModel> e)
    : IDirectionalEntityView(t, std::move(e), 2), m_baseSprite(t) {}

void IGhostView::update() {
    switch (std::static_pointer_cast<IGhost>(getCoupledEntity())->getMode()) {
    case GhostMode::WAITING:
    case GhostMode::DEAD:
    case GhostMode::CHASING:
        if (m_currentSprite != m_baseSprite) {
            m_currentSprite = m_baseSprite;
            m_topBase = m_currentSprite.top;
        }
        IDirectionalEntityView::update();
        break;
    case GhostMode::PANICKING:
        if (const auto panic_sprite = Assets::getSpriteInfo(Assets::GhostPanicBase); m_currentSprite != panic_sprite) {
            m_currentSprite = panic_sprite;
            m_topBase = m_currentSprite.top;
        }
        IDirectionalEntityView::update();
        break;
    }
}

BlueGhostView::BlueGhostView(std::shared_ptr<IEntityModel> e)
    : IGhostView(Assets::getSpriteInfo(Assets::GhostBlueBase), std::move(e)) {}

PinkGhostView::PinkGhostView(std::shared_ptr<IEntityModel> e)
    : IGhostView(Assets::getSpriteInfo(Assets::GhostPinkBase), std::move(e)) {}

OrangeGhostView::OrangeGhostView(std::shared_ptr<IEntityModel> e)
    : IGhostView(Assets::getSpriteInfo(Assets::GhostOrangeBase), std::move(e)) {}

RedGhostView::RedGhostView(std::shared_ptr<IEntityModel> e)
    : IGhostView(Assets::getSpriteInfo(Assets::GhostRedBase), std::move(e)) {}
