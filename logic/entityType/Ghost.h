#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "IEntityModel.h"
#include "LogicConstants.h"

enum class GhostMode {
    CHASING,
    PANICKING,
    WAITING
};


/**
 * @brief Virtual class to base specific Ghost types on
 */
class IGhost : public IEntityModel {
protected:
    GhostMode m_currentMode;
    double m_speed = LogicConstants::BASE_SPEED * 0.8;
    IGhost(const Rectangle& pos, GhostMode start_mode);

public:
    /**
     * @brief Calls the correct double dispatch
     * @param visitor Singularly dispatched visitor object
     */
    void accept(IEntityVisitor& visitor) override;

    [[nodiscard]] GhostMode getMode() const;
    /**
     * @return The Ghost's speed
     */
    [[nodiscard]] double getSpeed() const;
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
