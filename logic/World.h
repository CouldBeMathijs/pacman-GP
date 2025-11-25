#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H
#include "AbstractEntityFactory.h"
#include "Subject.h"
#include "entity_types/Pacman.h"

#include <string>
#include <vector>

class World {
private:
    std::vector<std::shared_ptr<EntityModel>> m_entities;
    std::shared_ptr<Pacman> pacman;
public:
    void addEntity(std::shared_ptr<EntityModel>);
    std::vector<std::shared_ptr<EntityModel>> getEntities();
    std::vector<std::shared_ptr<EntityModel>> getEntitiesInBounds(const Rectangle& boundBox);
    void setPacman(const std::shared_ptr<Pacman>& p);
    std::shared_ptr<Pacman> getPacman();
    void update(Direction);
    World() = default;
};

class WorldCreator {
public:
    static World createWorldFromFile(const std::string& filename, const std::shared_ptr<AbstractEntityFactory>& factory);
};

#endif // PACMAN_WORLD_H
