#include "ConcreteEntityFactory.h"

#include "EntityView.h"
#include "entity_types/Collectable.h"
#include "entity_types/Wall.h"
#include "entity_types/Pacman.h"
#include "entity_types/Ghost.h"
std::shared_ptr<EntityModel> ConcreteEntityFactory::createPacman(const Rectangle& p) {
    return createEntityWithView<Pacman, PacmanView>(p);
}

std::shared_ptr<EntityModel> ConcreteEntityFactory::createWall(const Rectangle& p) {
    return createEntityWithView<Wall, WallView>(p);
}

std::shared_ptr<EntityModel> ConcreteEntityFactory::createCoin(const Rectangle& p) {
    return createEntityWithView<Coin, CoinView>(p);
}

std::shared_ptr<EntityModel> ConcreteEntityFactory::createFruit(const Rectangle& p) {
    return createEntityWithView<Fruit, FruitView>(p);
}

std::shared_ptr<EntityModel> ConcreteEntityFactory::createOrangeGhost(const Rectangle& p) {
    // Calls the template with OrangeGhost Model and OrangeGhostView
    return createEntityWithView<OrangeGhost, OrangeGhostView>(p);
}

std::shared_ptr<EntityModel> ConcreteEntityFactory::createRedGhost(const Rectangle& p) {
    // Calls the template with RedGhost Model and RedGhostView
    return createEntityWithView<RedGhost, RedGhostView>(p);
}

std::shared_ptr<EntityModel> ConcreteEntityFactory::createBlueGhost(const Rectangle& p) {
    // Calls the template with BlueGhost Model and BlueGhostView
    return createEntityWithView<BlueGhost, BlueGhostView>(p);
}

std::shared_ptr<EntityModel> ConcreteEntityFactory::createPinkGhost(const Rectangle& p) {
    // Calls the template with PinkGhost Model and PinkGhostView
    return createEntityWithView<PinkGhost, PinkGhostView>(p);
}