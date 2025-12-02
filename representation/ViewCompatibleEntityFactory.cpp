#include "ViewCompatibleEntityFactory.h"

#include "EntityView.h"
#include "ScoreView.h"
#include "entity_types/Collectable.h"
#include "entity_types/Ghost.h"
#include "entity_types/Pacman.h"
#include "entity_types/Wall.h"

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
    // Calls the template with OrangeGhost Model and OrangeGhostView
    return createEntityWithView<OrangeGhost, OrangeGhostView>(p);
}

std::shared_ptr<EntityModel> ViewCompatibleEntityFactory::createRedGhost(const Rectangle& p) {
    // Calls the template with RedGhost Model and RedGhostView
    return createEntityWithView<RedGhost, RedGhostView>(p);
}

std::shared_ptr<EntityModel> ViewCompatibleEntityFactory::createBlueGhost(const Rectangle& p) {
    // Calls the template with BlueGhost Model and BlueGhostView
    return createEntityWithView<BlueGhost, BlueGhostView>(p);
}

std::shared_ptr<EntityModel> ViewCompatibleEntityFactory::createPinkGhost(const Rectangle& p) {
    // Calls the template with PinkGhost Model and PinkGhostView
    return createEntityWithView<PinkGhost, PinkGhostView>(p);
}