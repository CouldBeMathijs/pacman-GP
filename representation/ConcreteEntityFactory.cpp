
#include "ConcreteEntityFactory.h"

#include "EntityView.h"
std::unique_ptr<EntityModel> ConcreteEntityFactory::createGhost(Position p) {
    auto ghost = std::make_unique<Ghost>(p);
    ghost->addObserver(std::make_unique<GhostView>());
    return std::move(ghost);
}
std::unique_ptr<EntityModel> ConcreteEntityFactory::createPacman(Position p) {
    auto pacman = std::make_unique<Pacman>(p);
    pacman->addObserver(std::make_unique<PacmanView>());
    return std::move(pacman);
}
std::unique_ptr<EntityModel> ConcreteEntityFactory::createWall(Position p) {
    auto wall = std::make_unique<Wall>(p);
    wall->addObserver(std::make_unique<WallView>());
    return std::move(wall);
}

std::unique_ptr<EntityModel> ConcreteEntityFactory::createCoin(Position p) {
    auto coin = std::make_unique<Coin>(p);
    coin->addObserver(std::make_unique<CoinView>());
    return std::move(coin);
}
std::unique_ptr<EntityModel> ConcreteEntityFactory::createFruit(Position p) {
    auto fruit = std::make_unique<Fruit>(p);
    fruit->addObserver(std::make_unique<FruitView>());
    return std::move(fruit);
}
