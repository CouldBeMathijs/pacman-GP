#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H
#include "AbstractEntityFactory.h"
#include "Subject.h"
#include "entity_types/Pacman.h"

#include <string>
#include <vector>

class World {
private:
    bool gameRunning = true;
    std::shared_ptr<Pacman> pacman;
    std::vector<std::shared_ptr<EntityModel>> m_entities;
    unsigned int amountOfLives = 3;
public:
    World() = default;
    std::shared_ptr<Pacman> getPacman();
    std::vector<std::shared_ptr<EntityModel>> getEntities();
    std::vector<std::shared_ptr<EntityModel>> getEntitiesInBounds(const Rectangle& boundBox);
    void addEntity(std::shared_ptr<EntityModel>);
    void setPacman(const std::shared_ptr<Pacman>& p);
    void update(Direction);
    [[nodiscard]] bool isRunning() const;
};

class WorldCreator {
public:
    static World createWorldFromFile(const std::string& filename, const std::shared_ptr<AbstractEntityFactory>& factory);
};

#endif // PACMAN_WORLD_H
