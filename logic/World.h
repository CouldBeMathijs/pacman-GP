#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H
#include "AbstractEntityFactory.h"
#include "Subject.h"

#include <vector>
#include <string>

class World {
private:
    std::vector<std::shared_ptr<EntityModel>> entities;
public:
    void addEntity(std::shared_ptr<EntityModel>);
    std::vector<std::shared_ptr<EntityModel>> getEntities();
    void update() const;
    World() = default;
};

class WorldCreator {
public:
    static World createWorldFromFile(const std::string& filename, const std::shared_ptr<AbstractEntityFactory>& factory);
};

#endif // PACMAN_WORLD_H
