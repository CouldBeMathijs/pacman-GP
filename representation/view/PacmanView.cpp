#include "PacmanView.h"

#include "entityType/Pacman.h"

#include <cmath>

PacmanView::PacmanView(std::shared_ptr<IEntityModel> e)
    : IDirectionalEntityView(Assets::getSpriteInfo(Assets::SpriteDefinition::PacmanBase), std::move(e), 3) {}

void PacmanView::update() {

    if (const double deathTimer = std::static_pointer_cast<Pacman>(getCoupledEntity())->getDeathTimer();
        deathTimer > 0) {
        if (!m_dying) {
            m_dying = !m_dying;
            m_currentSprite = Assets::getSpriteInfo(Assets::SpriteDefinition::PacmanDeathBase);
            m_amountOfTextures = 10;
            m_currentTextureOffset = 0;
        }
        IEntityView::update();
    } else {
        if (m_dying) {
            m_dying = !m_dying;
            m_currentSprite = Assets::getSpriteInfo(Assets::SpriteDefinition::PacmanBase);
            m_currentTextureOffset = 0;
            m_amountOfTextures = 3;
        }
        IDirectionalEntityView::update();
    }
}