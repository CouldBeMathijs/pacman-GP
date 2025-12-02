#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H
#include "AbstractEntityFactory.h"
#include "Subject.h"
#include "entity_types/Pacman.h"

#include <string>
#include <vector>

/**
 * @brief The different states a World can be in
 */
enum class WorldState { RUNNING, VICTORY, GAME_OVER };

/**
 * @brief In charge of holding entities, collision checks and coordinating movement.
 */
class World {
private:
    WorldState m_worldState = WorldState::RUNNING;
    std::shared_ptr<Pacman> m_pacman;
    std::vector<std::shared_ptr<EntityModel>> m_entities;

public:
    World() = default;
    std::shared_ptr<Pacman> getPacman();
    std::vector<std::shared_ptr<EntityModel>> getEntities();
    std::vector<std::shared_ptr<EntityModel>> getEntitiesInBounds(const Rectangle& boundBox);
    void addEntity(std::shared_ptr<EntityModel>);
    void setPacman(const std::shared_ptr<Pacman>& p);
    void update(Direction);
    [[nodiscard]] WorldState getState() const;
};

class WorldCreator {
public:
    static World createWorldFromFile(const std::string& filename,
                                     const std::shared_ptr<AbstractEntityFactory>& factory);
};

#endif // PACMAN_WORLD_H
