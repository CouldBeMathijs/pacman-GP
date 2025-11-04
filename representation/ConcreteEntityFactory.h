
#ifndef PACMAN_CONCRETEENTITYFACTORY_H
#define PACMAN_CONCRETEENTITYFACTORY_H
#include "AbstractEntityFactory.h"

class ConcreteEntityFactory final : public AbstractEntityFactory {
public:
    std::unique_ptr<EntityModel> createCoin(Position) override;
    std::unique_ptr<EntityModel> createFruit(Position) override;
    std::unique_ptr<EntityModel> createGhost(Position) override;
    std::unique_ptr<EntityModel> createPacman(Position) override;
    std::unique_ptr<EntityModel> createWall(Position) override;
};

#endif // PACMAN_CONCRETEENTITYFACTORY_H
