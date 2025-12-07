#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "IEntityModel.h"
#include "LogicConstants.h"

/**
 * @brief Different movement modes Ghosts can be in
 */
enum class GhostMode { CHASING, PANICKING, WAITING };

enum class ChasingAlgorithm { DIRECTIONAL, IN_FRONT_MANHATTAN, ON_TOP_MANHATTAN };

/**
 * @brief Virtual class to base on which to base specific Ghost types
 */
class IGhost : public IEntityModel {
protected:
    ChasingAlgorithm m_algorithm;
    GhostMode m_currentMode;
    Position m_spawnPoint;
    double m_amount_of_seconds_left_in_current_mode;
    double m_speed = LogicConstants::BASE_SPEED * 0.8;

    IGhost(const Rectangle& pos, GhostMode start_mode, double amountOfSecondsLeftInCurrentMode,
           ChasingAlgorithm algorithm);

public:
    /**
     * @brief Calls the correct double dispatch
     * @param visitor Singularly dispatched visitor object
     */
    void accept(IEntityVisitor& visitor) override;

    /**
     * @return The Ghost's current mode
     */
    [[nodiscard]] GhostMode getMode() const;

    /**
     * @return The Ghost's speed
     */
    [[nodiscard]] double getSpeed() const;

    void goToSpawn();
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
