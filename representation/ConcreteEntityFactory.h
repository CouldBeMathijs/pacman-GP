
#ifndef PACMAN_CONCRETEENTITYFACTORY_H
#define PACMAN_CONCRETEENTITYFACTORY_H
#include "AbstractEntityFactory.h"

class ConcreteEntityFactory final : public AbstractEntityFactory {
public:
    Coin createCoin(Position) override;
    Fruit createFruit(Position) override;
    Ghost createGhost(Position) override;
    Pacman createPacman(Position) override;
    Wall createWall(Position) override;
};

#endif // PACMAN_CONCRETEENTITYFACTORY_H
