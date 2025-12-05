#ifndef PACMAN_ENTITY_VIEW_H
#define PACMAN_ENTITY_VIEW_H
#include "Observer.h"

#include "../AssetManager.h"
#include "IEntityModel.h"
#include <SFML/Graphics.hpp>

#include <memory>

/**
 * @brief Virtual class providing the common ground needed for displaying entities
 */
class IEntityView : public Observer {
private:
    bool m_animationCycleMovingUp = true;
    const double m_timePerFrame = 0.12;
    double m_timeAccumulator = 0.0;
    std::shared_ptr<IEntityModel> m_coupledEntity;

protected:
    Assets::TextureLocation m_currentSprite;
    explicit IEntityView(Assets::TextureLocation, std::shared_ptr<IEntityModel>);
    unsigned int m_amountOfTextures = 1;
    unsigned int m_currentTextureOffset = 0;

public:
    void update() override;
    void animate();
    [[nodiscard]] unsigned int getCurrentTextureOffset() const;
    std::shared_ptr<IEntityModel> getCoupledEntity();
};

#endif
