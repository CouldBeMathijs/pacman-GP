#ifndef PACMAN_ENTITYVIEW_H
#define PACMAN_ENTITYVIEW_H
#include "Observer.h"

#include "AssetManager.h"
#include "EntityModel.h"
#include <SFML/Graphics.hpp>

#include <memory>

/**
 * @brief Virtual class providing the common ground needed for displaying entities with SFML
 */
class EntityView : public Observer {
private:
    bool m_animationCycleMovingUp = true;
    const double m_timePerFrame = 0.12;
    double m_timeAccumulator = 0.0;
    std::shared_ptr<EntityModel> m_coupledEntity;

protected:
    Assets::TextureLocation m_currentSprite;
    explicit EntityView(Assets::TextureLocation, std::shared_ptr<EntityModel>);
    unsigned int m_amountOfTextures = 1;
    unsigned int m_currentTextureOffset = 0;

public:
    void update() override;
    void animate();
    [[nodiscard]] unsigned int getCurrentTextureOffset() const;
    std::shared_ptr<EntityModel> getCoupledEntity();
};

class DirectionalEntityView : public EntityView {
private:
    int m_topBase = m_currentSprite.top;

protected:
    DirectionalEntityView(Assets::TextureLocation m, std::shared_ptr<EntityModel> n, int amountOfTextures);

public:
    void update() override;
};

class BlueGhostView final : public DirectionalEntityView {
public:
    explicit BlueGhostView(std::shared_ptr<EntityModel>);
};

class OrangeGhostView final : public DirectionalEntityView {
public:
    explicit OrangeGhostView(std::shared_ptr<EntityModel>);
};

class PinkGhostView final : public DirectionalEntityView {
public:
    explicit PinkGhostView(std::shared_ptr<EntityModel>);
};

class RedGhostView final : public DirectionalEntityView {
public:
    explicit RedGhostView(std::shared_ptr<EntityModel>);
};

class CoinView final : public EntityView {
public:
    explicit CoinView(std::shared_ptr<EntityModel>);
};

class FruitView final : public EntityView {
public:
    explicit FruitView(std::shared_ptr<EntityModel>);
};

class PacmanView final : public DirectionalEntityView {
public:
    explicit PacmanView(std::shared_ptr<EntityModel>);
};

class WallView final : public EntityView {
public:
    explicit WallView(std::shared_ptr<EntityModel>);
};

#endif // PACMAN_ENTITYVIEW_H
