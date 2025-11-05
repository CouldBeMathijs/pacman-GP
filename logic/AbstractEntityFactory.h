
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
    virtual std::unique_ptr<EntityModel> createPacman(Position) = 0;
    std::unique_ptr<EntityModel> createPacman(const double x, const double y) {
        return createPacman({x, y});
    }
    virtual std::unique_ptr<EntityModel> createGhost(Position) = 0;
    std::unique_ptr<EntityModel> createGhost(const double x, const double y) {
        return createGhost({x, y});
    }
    virtual std::unique_ptr<EntityModel> createWall(Position) = 0;
    std::unique_ptr<EntityModel> createWall(const double x, const double y) {
        return createWall({x, y});
    }
    virtual std::unique_ptr<EntityModel> createCoin(Position) = 0;
    std::unique_ptr<EntityModel> createCoin(const double x, const double y) {
        return createCoin({x, y});
    }
    virtual std::unique_ptr<EntityModel> createFruit(Position) = 0;
    std::unique_ptr<EntityModel> createFruit(const double x, const double y) {
        return createFruit({x, y});
    }
};

#endif // PACMAN_ABSTRACTENTITYFACTORY_H
