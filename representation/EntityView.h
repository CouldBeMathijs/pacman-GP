
#ifndef PACMAN_ENTITYVIEW_H
#define PACMAN_ENTITYVIEW_H
#include "Observer.h"

#include "Spritemap.h"
#include "Subject.h"
#include <SFML/Graphics.hpp>

#include <memory>

class EntityView : public Observer {
private:
    std::shared_ptr<EntityModel> coupledEntity;
    unsigned int currentTextureOffset = 0;
    bool animationCycleMovingUp = true;
    const double timePerFrame = 0.12;
    double timeAccumulator = 0.0;
protected:
    Spritemap::SpriteInfo base;
    unsigned int amountOfTextures = 1;
    explicit EntityView(Spritemap::SpriteInfo, std::shared_ptr<EntityModel>);
public:
    void update() override;
    void animate();
};

class DirectionalEntityView : public EntityView {
private:

protected:
    DirectionalEntityView(Spritemap::SpriteInfo m, std::shared_ptr<EntityModel> n, int amountOfTextures);
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
