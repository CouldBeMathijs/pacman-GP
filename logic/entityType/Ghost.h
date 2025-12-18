#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "IDirectionalEntityModel.h"
#include "LogicConstants.h"

#include <iostream>
#include <stack>

/**
 * @brief Different movement modes Ghosts can be in
 */
enum class GhostMode { CHASING, PANICKING, WAITING, DEAD };

const char* to_string(GhostMode e);

enum class ChasingAlgorithm { DIRECTIONAL, IN_FRONT_MANHATTAN, ON_TOP_MANHATTAN };

const char* to_string(ChasingAlgorithm e);

struct GhostState {
    GhostMode mode;
    double timer;
};

class GhostModeStack final : std::stack<GhostState> {
public:
    using std::stack<GhostState>::push;
    using std::stack<GhostState>::pop;
    using std::stack<GhostState>::top;
    using std::stack<GhostState>::empty;
    using std::stack<GhostState>::size;
};

/**
 * @brief Virtual class to base on which to base specific Ghost types
 */
class IGhost : public IDirectionalEntityModel {
protected:
    ChasingAlgorithm m_algorithm;
    Direction::Cardinal m_wantedDirection = Direction::Cardinal::NORTH;
    GhostModeStack m_stateStack;
    bool m_isMovingAwayFromSpawn = true;
    double m_amount_of_seconds_until_able_to_turn = 0;
    double m_speed = LogicConstants::BASE_SPEED * 0.8;

    IGhost(const Rectangle& pos, GhostMode start_mode, double amountOfSecondsLeftInCurrentMode,
           ChasingAlgorithm algorithm);

public:
    [[nodiscard]] ChasingAlgorithm getAlgorithm() const;
    [[nodiscard]] Direction::Cardinal getWantedDirection() const;
    [[nodiscard]] GhostMode getMode() const;
    [[nodiscard]] bool allowedToTurn() const;
    [[nodiscard]] bool isMovingAwayFromSpawn() const;
    bool isBlocked(const std::vector<std::shared_ptr<IEntityModel>>& touchingEntities) override;

    void displayInfo() const;

    /**
     * @brief Calls the correct double dispatch
     * @param visitor Singularly dispatched visitor object
     */
    void accept(IEntityVisitor& visitor) override;
    void goToSpawn() override;
    void hasExitedSpawn();
    void hasTurned();
    void setMode(GhostMode);
    void setWantedDirection(Direction::Cardinal d);
    void update(Direction::Cardinal) override;
};

class BlueGhost final : public IGhost {
public:
    explicit BlueGhost(const Rectangle& pos);
};

class PinkGhost final : public IGhost {
public:
    explicit PinkGhost(const Rectangle& pos);
};

class OrangeGhost final : public IGhost {
public:
    explicit OrangeGhost(const Rectangle& pos);
};

class RedGhost final : public IGhost {
public:
    explicit RedGhost(const Rectangle& pos);
};

#endif // PACMAN_GHOST_H
