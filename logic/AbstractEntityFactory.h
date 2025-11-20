
#ifndef PACMAN_ABSTRACTENTITYFACTORY_H
#define PACMAN_ABSTRACTENTITYFACTORY_H
#include "Subject.h"

#include <memory>

class AbstractEntityFactory {
protected:
    AbstractEntityFactory() = default;
public:
    virtual ~AbstractEntityFactory() = default;

    virtual std::shared_ptr<EntityModel> createPacman(const Position& pos) = 0;
    virtual std::shared_ptr<EntityModel> createBlueGhost(const Position& pos) = 0;
    virtual std::shared_ptr<EntityModel> createPinkGhost(const Position& pos) = 0;
    virtual std::shared_ptr<EntityModel> createOrangeGhost(const Position& pos) = 0;
    virtual std::shared_ptr<EntityModel> createRedGhost(const Position& pos) = 0;
    virtual std::shared_ptr<EntityModel> createWall(const Position& pos) = 0;
    virtual std::shared_ptr<EntityModel> createCoin(const Position& pos) = 0;
    virtual std::shared_ptr<EntityModel> createFruit(const Position& pos) = 0;


    std::shared_ptr<EntityModel> createPacman(const double x, const double y) {
        return createPacman({x, y});
    }
    std::shared_ptr<EntityModel> createBlueGhost(const double x, const double y) {
        return createBlueGhost({x, y});
    }
    std::shared_ptr<EntityModel> createPinkGhost(const double x, const double y) {
        return createPinkGhost({x, y});
    }
    std::shared_ptr<EntityModel> createOrangeGhost(const double x, const double y) {
        return createOrangeGhost({x, y});
    }
    std::shared_ptr<EntityModel> createRedGhost(const double x, const double y) {
        return createRedGhost({x, y});
    }
    std::shared_ptr<EntityModel> createWall(const double x, const double y) {
        return createWall({x, y});
    }
    std::shared_ptr<EntityModel> createCoin(const double x, const double y) {
        return createCoin({x, y});
    }
    std::shared_ptr<EntityModel> createFruit(const double x, const double y) {
        return createFruit({x, y});
    }
};

#endif // PACMAN_ABSTRACTENTITYFACTORY_H
