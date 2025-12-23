#include "PacmanView.h"

#include "entityType/Pacman.h"

#include <cmath>

PacmanView::PacmanView(std::shared_ptr<IEntityModel> e)
    : IDirectionalEntityView(Assets::getSpriteInfo(Assets::SpriteDefinition::PacmanBase), std::move(e), 3) {}

void PacmanView::update() {

    if (double deathTimer = std::static_pointer_cast<Pacman>(getCoupledEntity())->getDeathTimer(); deathTimer > 0) {
        // 1. Reset to the base death sprite
        m_currentSprite = Assets::getSpriteInfo(Assets::SpriteDefinition::PacmanDeathBase);

        // 2. Calculate frame index.
        // If the animation goes from start to finish as timer goes from Max to 0:
        const int frameOffset = std::floor(10 * (LogicConstants::ANIMATION_SPEED * 10 - deathTimer));

        // Multiply by the height of a single frame (e.g., 16 pixels)
        m_currentSprite.top += (frameOffset * 50);

        // 3. Manually call the base drawing logic but skip IDirectionalEntityView
        // to avoid directional sprite overrides.
        IEntityView::update();
    } else {
        // Normal behavior
        m_currentSprite = Assets::getSpriteInfo(Assets::SpriteDefinition::PacmanBase);
        IDirectionalEntityView::update();
    }
}