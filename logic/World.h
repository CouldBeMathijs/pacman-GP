#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H
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
    static World createWorldFromFile(const std::string& filename);
};

#endif // PACMAN_WORLD_H
