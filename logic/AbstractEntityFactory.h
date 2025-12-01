#ifndef PACMAN_ABSTRACTENTITYFACTORY_H
#define PACMAN_ABSTRACTENTITYFACTORY_H
#include "Subject.h"

#include <memory>

class AbstractEntityFactory {
protected:
    AbstractEntityFactory() = default;

public:
    virtual ~AbstractEntityFactory() = default;

    virtual std::shared_ptr<EntityModel> createPacman(const Rectangle& pos) = 0;
    virtual std::shared_ptr<EntityModel> createBlueGhost(const Rectangle& pos) = 0;
    virtual std::shared_ptr<EntityModel> createPinkGhost(const Rectangle& pos) = 0;
    virtual std::shared_ptr<EntityModel> createOrangeGhost(const Rectangle& pos) = 0;
    virtual std::shared_ptr<EntityModel> createRedGhost(const Rectangle& pos) = 0;
    virtual std::shared_ptr<EntityModel> createWall(const Rectangle& pos) = 0;
    virtual std::shared_ptr<EntityModel> createCoin(const Rectangle& pos) = 0;
    virtual std::shared_ptr<EntityModel> createFruit(const Rectangle& pos) = 0;
};

#endif // PACMAN_ABSTRACTENTITYFACTORY_H
