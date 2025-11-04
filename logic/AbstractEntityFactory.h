
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
    virtual EntityModel createPacman(Position) = 0;
    EntityModel createPacman(const double x, const double y) {
        return createPacman({x, y});
    }
    virtual EntityModel createGhost(Position) = 0;
    EntityModel createGhost(const double x, const double y) {
        return createGhost({x, y});
    }
    virtual EntityModel createWall(Position) = 0;
    EntityModel createWall(const double x, const double y) {
        return createWall({x, y});
    }
    virtual EntityModel createCoin(Position) = 0;
    EntityModel createCoint(const double x, const double y) {
        return createCoin({x, y});
    }
    virtual EntityModel createFruit(Position) = 0;
    EntityModel createFruit(const double x, const double y) {
        return createFruit({x, y});
    }
};

#endif // PACMAN_ABSTRACTENTITYFACTORY_H
