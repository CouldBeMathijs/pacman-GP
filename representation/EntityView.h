#ifndef PACMAN_ENTITY_VIEW_H
#define PACMAN_ENTITY_VIEW_H
#include "Observer.h"

#include "AssetManager.h"
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

/**
 * @brief Virtual class providing the common ground needed for displaying direction entities
 */
class IDirectionalEntityView : public IEntityView {
private:
    int m_topBase = m_currentSprite.top;

protected:
    IDirectionalEntityView(Assets::TextureLocation m, std::shared_ptr<IEntityModel> n, int amountOfTextures);

public:
    void update() override;
};

class BlueGhostView final : public IDirectionalEntityView {
public:
    explicit BlueGhostView(std::shared_ptr<IEntityModel>);
};

class OrangeGhostView final : public IDirectionalEntityView {
public:
    explicit OrangeGhostView(std::shared_ptr<IEntityModel>);
};

class PinkGhostView final : public IDirectionalEntityView {
public:
    explicit PinkGhostView(std::shared_ptr<IEntityModel>);
};

class RedGhostView final : public IDirectionalEntityView {
public:
    explicit RedGhostView(std::shared_ptr<IEntityModel>);
};

class CoinView final : public IEntityView {
public:
    explicit CoinView(std::shared_ptr<IEntityModel>);
};

class FruitView final : public IEntityView {
public:
    explicit FruitView(std::shared_ptr<IEntityModel>);
};

class PacmanView final : public IDirectionalEntityView {
public:
    explicit PacmanView(std::shared_ptr<IEntityModel>);
    void update() override;
};

class WallView final : public IEntityView {
public:
    explicit WallView(std::shared_ptr<IEntityModel>);
};

#endif
