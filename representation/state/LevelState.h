#ifndef PACMAN_LEVELSTATE_H
#define PACMAN_LEVELSTATE_H
#include "../ViewCompatibleEntityFactory.h"
#include "IState.h"
#include "World.h"

/**
 * @brief Game State in charge of the main game Window, controls the world and factory
 * * On Game Over: goes to Game Over state and requests its own deletion
 * * On Victory: goes to Victory and requests its own deletion
 * * On Escape: call the pause state
 */
class LevelState final : public IState {
private:
    World m_world;
    std::shared_ptr<ViewCompatibleEntityFactory> m_factory;

public:
    LevelState();
    void update(Direction::Cardinal) override;
    void handleInput(const sf::Event&) override;
};

#endif // PACMAN_LEVELSTATE_H
