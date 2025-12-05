#ifndef PACMAN_I_DIRECTIONAL_ENTITY_VIEW_H
#define PACMAN_I_DIRECTIONAL_ENTITY_VIEW_H
#include "IEntityView.h"

/**
 * @brief Virtual class providing the common ground needed for displaying direction entities
 */
class IDirectionalEntityView : public IEntityView {
protected:
    int m_topBase = m_currentSprite.top;
    IDirectionalEntityView(Assets::TextureLocation m, std::shared_ptr<IEntityModel> n, int amountOfTextures);

public:
    void update() override;
};

#endif
