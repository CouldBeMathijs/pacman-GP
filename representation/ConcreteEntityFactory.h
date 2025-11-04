
#ifndef PACMAN_CONCRETEENTITYFACTORY_H
#define PACMAN_CONCRETEENTITYFACTORY_H
#include "AbstractEntityFactory.h"

class ConcreteEntityFactory final : public AbstractEntityFactory {
public:
    EntityModel createCoin(Position) override;
    EntityModel createFruit(Position) override;
    EntityModel createGhost(Position) override;
    EntityModel createPacman(Position) override;
    EntityModel createWall(Position) override;
};

#endif // PACMAN_CONCRETEENTITYFACTORY_H
