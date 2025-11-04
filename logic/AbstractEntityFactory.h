
#ifndef PACMAN_ABSTRACTENTITYFACTORY_H
#define PACMAN_ABSTRACTENTITYFACTORY_H
#include "entity_types/Ghost.h"
#include "entity_types/Pacman.h"
#include "entity_types/Wall.h"

class AbstractEntityFactory {
protected:
    AbstractEntityFactory() = default;

public:
    Pacman createPacman();
    Ghost createGhost();
    Wall createWall();

};

#endif // PACMAN_ABSTRACTENTITYFACTORY_H
