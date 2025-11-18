#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H
#include "AbstractEntityFactory.h"
#include "Subject.h"

#include <vector>
#include <string>

class World {
private:
    std::vector<std::unique_ptr<EntityModel>> entities;
public:
    void addEntity(std::unique_ptr<EntityModel>);
    void update() const;
    World() = default;
};

class WorldCreator {
public:
    static World createWorldFromFile(const std::string& filename, const std::shared_ptr<AbstractEntityFactory>& factory);
};

#endif // PACMAN_WORLD_H
