
#ifndef PACMAN_ENTITYVIEW_H
#define PACMAN_ENTITYVIEW_H
#include "Observer.h"

#include <SFML/Graphics.hpp>
#include <vector>

class EntityView : public Observer {
private:
    std::vector<sf::Sprite> m_sprites;

protected:
    explicit EntityView(std::vector<sf::Sprite>);
public:
    void update() override;
};

class DirectionalEntityView : public EntityView {

};

class CoinView final : public EntityView {
public:
    explicit CoinView();
};
class FruitView final : public EntityView {
public:
    explicit FruitView();
};
class GhostView final : public EntityView {
public:
    explicit GhostView();
};
class PacmanView final : public EntityView {
public:
    explicit PacmanView();
};
class WallView final : public EntityView {
public:
    explicit WallView();
};

#endif // PACMAN_ENTITYVIEW_H
