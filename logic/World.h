#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H
#include "ISubject.h"
#include "entityType/Ghost.h"
#include "entityType/Pacman.h"

#include <vector>

/**
 * @brief The different states a World can be in
 */
enum class WorldState { RUNNING, VICTORY, GAME_OVER };

/**
 * @brief In charge of holding entities, collision checks and coordinating movement.
 */
class World {
    WorldState m_worldState = WorldState::RUNNING;
    std::shared_ptr<Pacman> m_pacman;
    std::vector<std::shared_ptr<IEntityModel>> m_nonMovingEntities;
    std::vector<std::shared_ptr<IGhost>> m_ghosts;

protected:
    void handleCollectables(const Rectangle& current_hb);
    void updatePacman(Direction d);

public:
    World() = default;
    [[nodiscard]] WorldState getState() const;
    [[nodiscard]] const std::shared_ptr<Pacman>& getPacman() const;
    [[nodiscard]] const std::vector<std::shared_ptr<IEntityModel>>& getNonMovingEntities() const;

    [[nodiscard]] const std::vector<std::shared_ptr<IGhost>>& getGhosts() const { return m_ghosts; };

    std::vector<std::shared_ptr<IEntityModel>> getEntitiesInBounds(const Rectangle& boundBox);
    void addGhost(std::shared_ptr<IGhost> ghost);
    void addNonMovingEntity(std::shared_ptr<IEntityModel>);
    void setPacman(const std::shared_ptr<Pacman>&);
    void update(Direction d);
    bool tryToMoveGhost(const IGhost& ghost);
    void updateGhosts(Direction d);
};

#endif // PACMAN_WORLD_H
