
#include "ConcreteEntityFactory.h"

#include "EntityView.h"
std::shared_ptr<EntityModel> ConcreteEntityFactory::createGhost(Position p) {
    auto ghost = std::make_shared<Ghost>(p);
    ghost->addObserver(std::make_shared<GhostView>(ghost));
    return std::move(ghost);
}
std::shared_ptr<EntityModel> ConcreteEntityFactory::createPacman(Position p) {
    auto pacman = std::make_shared<Pacman>(p);
    pacman->addObserver(std::make_shared<PacmanView>(pacman));
    return std::move(pacman);
}
std::shared_ptr<EntityModel> ConcreteEntityFactory::createWall(Position p) {
    auto wall = std::make_shared<Wall>(p);
    wall->addObserver(std::make_shared<WallView>(wall));
    return std::move(wall);
}
std::shared_ptr<EntityModel> ConcreteEntityFactory::createCoin(Position p) {
    auto coin = std::make_shared<Coin>(p);
    coin->addObserver(std::make_shared<CoinView>(coin));
    return std::move(coin);
}
std::shared_ptr<EntityModel> ConcreteEntityFactory::createFruit(Position p) {
    auto fruit = std::make_shared<Fruit>(p);
    fruit->addObserver(std::make_shared<FruitView>(fruit));
    return std::move(fruit);
}
