#include "ViewCompatibleEntityFactory.h"

#include "EntityType/Collectable.h"
#include "EntityType/Ghost.h"
#include "EntityType/Pacman.h"
#include "EntityType/Wall.h"
#include "EntityView.h"
#include "ScoreView.h"

std::shared_ptr<EntityModel> ViewCompatibleEntityFactory::createPacman(const Rectangle& p) {
    auto pacman = createEntityWithView<Pacman, PacmanView>(p);
    const auto view = std::make_shared<ScoreView>();
    pacman->addObserver(view);
    return pacman;
}

std::shared_ptr<EntityModel> ViewCompatibleEntityFactory::createWall(const Rectangle& p) {
    return createEntityWithView<Wall, WallView>(p);
}

std::shared_ptr<EntityModel> ViewCompatibleEntityFactory::createCoin(const Rectangle& p) {
    return createEntityWithView<Coin, CoinView>(p);
}

std::shared_ptr<EntityModel> ViewCompatibleEntityFactory::createFruit(const Rectangle& p) {
    return createEntityWithView<Fruit, FruitView>(p);
}

std::shared_ptr<EntityModel> ViewCompatibleEntityFactory::createOrangeGhost(const Rectangle& p) {
    return createEntityWithView<OrangeGhost, OrangeGhostView>(p);
}

std::shared_ptr<EntityModel> ViewCompatibleEntityFactory::createRedGhost(const Rectangle& p) {
    return createEntityWithView<RedGhost, RedGhostView>(p);
}

std::shared_ptr<EntityModel> ViewCompatibleEntityFactory::createBlueGhost(const Rectangle& p) {
    return createEntityWithView<BlueGhost, BlueGhostView>(p);
}

std::shared_ptr<EntityModel> ViewCompatibleEntityFactory::createPinkGhost(const Rectangle& p) {
    return createEntityWithView<PinkGhost, PinkGhostView>(p);
}