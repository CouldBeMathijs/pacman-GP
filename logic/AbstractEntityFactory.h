
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
    virtual Pacman createPacman() = 0;
    virtual Ghost createGhost() = 0;
    virtual Wall createWall() = 0;
    virtual Coin createCoin() = 0;
    virtual Fruit createFruit() = 0;
};

#endif // PACMAN_ABSTRACTENTITYFACTORY_H
