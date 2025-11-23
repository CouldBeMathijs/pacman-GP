#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H
#include "AbstractEntityFactory.h"
#include "Subject.h"

#include <vector>
#include <string>

class World {
private:
    std::vector<std::shared_ptr<EntityModel>> m_entities;
public:
    void addEntity(std::shared_ptr<EntityModel>);
    std::vector<std::shared_ptr<EntityModel>> getEntities();
    std::vector<std::shared_ptr<EntityModel>> getEntitiesInBounds(Position topleft, Position bottomright);
    void update(Direction) const;
    World() = default;
};

class WorldCreator {
public:
    static World createWorldFromFile(const std::string& filename, std::shared_ptr<AbstractEntityFactory> factory);
};

#endif // PACMAN_WORLD_H
