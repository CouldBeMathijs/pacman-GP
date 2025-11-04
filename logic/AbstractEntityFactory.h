
#ifndef PACMAN_ABSTRACTENTITYFACTORY_H
#define PACMAN_ABSTRACTENTITYFACTORY_H
#include "entity_types/Collectable.h"
#include "entity_types/Ghost.h"
#include "entity_types/Pacman.h"
#include "entity_types/Wall.h"

class AbstractEntityFactory {
protected:
    AbstractEntityFactory() = default;
public:
    virtual ~AbstractEntityFactory() = default;
    virtual Pacman createPacman(Position) = 0;
    Pacman createPacman(const double x, const double y) {
        return createPacman({x, y});
    }
    virtual Ghost createGhost(Position) = 0;
    Ghost createGhost(const double x, const double y) {
        return createGhost({x, y});
    }
    virtual Wall createWall(Position) = 0;
    Wall createWall(const double x, const double y) {
        return createWall({x, y});
    }
    virtual Coin createCoin(Position) = 0;
    Coin createCoint(const double x, const double y) {
        return createCoin({x, y});
    }
    virtual Fruit createFruit(Position) = 0;
    Fruit createFruit(const double x, const double y) {
        return createFruit({x, y});
    }
};

#endif // PACMAN_ABSTRACTENTITYFACTORY_H
