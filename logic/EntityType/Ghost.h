#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "EntityModel.h"
#include "LogicConstants.h"

/**
 * @brief Virtual class to base specific Ghost types on
 */
class AbstractGhost : public EntityModel {
protected:
    double m_speed = LogicConstants::BASE_SPEED * 0.8;
    explicit AbstractGhost(const Rectangle& pos);

    /**
     * @brief Calls the correct double dispatch
     * @param visitor Singularly dispatched visitor object
     */
    void accept(IEntityVisitor& visitor) override;


    /**
     * @return The Ghost's speed
     */
    [[nodiscard]] double getSpeed() const;
};

class BlueGhost final : public AbstractGhost {
public:
    explicit BlueGhost(const Rectangle& pos);
};

class PinkGhost final : public AbstractGhost {
public:
    explicit PinkGhost(const Rectangle& pos);
};

class OrangeGhost final : public AbstractGhost {
public:
    explicit OrangeGhost(const Rectangle& pos);
};

class RedGhost final : public AbstractGhost {
public:
    explicit RedGhost(const Rectangle& pos);
};

#endif // PACMAN_GHOST_H
