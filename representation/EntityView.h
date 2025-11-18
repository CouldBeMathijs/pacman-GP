
#ifndef PACMAN_ENTITYVIEW_H
#define PACMAN_ENTITYVIEW_H
#include "Observer.h"

#include <SFML/Graphics.hpp>
#include "Spritemap.h"

class EntityView : public Observer {
private:
    Spritemap::SpriteInfo base;

protected:
    explicit EntityView(Spritemap::SpriteInfo);
public:
    void update() override;
};

class DirectionalEntityView : public EntityView {
private:
    unsigned int amountOfTextures;
protected:
    explicit DirectionalEntityView(Spritemap::SpriteInfo, unsigned int amountOfTextures);
};

class CoinView final : public EntityView {
public:
    explicit CoinView();
};

class FruitView final : public EntityView {
public:
    explicit FruitView();
};

class GhostView final : public DirectionalEntityView {
public:
    explicit GhostView();
};

class PacmanView final : public DirectionalEntityView {
public:
    explicit PacmanView();
};

class WallView final : public EntityView {
public:
    explicit WallView();
};

#endif // PACMAN_ENTITYVIEW_H
