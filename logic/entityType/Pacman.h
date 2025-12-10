#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "IEntityModel.h"
#include "LogicConstants.h"
#include "ScoreKeeper.h"

/**
 * @brief The player character
 */
class Pacman final : public IEntityModel {
private:
    Position m_spawnPoint = getHitBox().topLeft;
    bool m_ghostTouch = false;
    bool m_isDying = false;
    double m_speed = LogicConstants::BASE_SPEED;

public:
    explicit Pacman(const Rectangle& pos);
    /**
     * @brief Getter for ghostTouch boolean
     * @return True if pacman has touched a Ghost, else false
     */
    [[nodiscard]] bool hasTouchedGhost() const;

    /**
     * @brief Getter for isDying boolean
     * @return True is pacman is dying, else false
     */
    [[nodiscard]] bool isDying() const;

    /**
     * @brief Getter for speed
     * @return Pacman's current speed
     */
    [[nodiscard]] double getSpeed() const;

    /**
     * @brief Calls the correct double dispatch
     * @param visitor Singularly dispatched visitor object
     */
    void accept(IEntityVisitor& visitor) override;

    /**
     * @brief Makes it so hasTouchedGhost() returns true until resetGhostTouch() is called
     */
    void ghostTouches();

    /**
     * @brief Return this sprite to the coordinate it was initially created at
     */
    void goToSpawn();

    /**
     * @brief Makes it so hasTouchedGhost() returns false until ghostTouches() is called
     */
    void resetGhostTouch();

    /**
     * @brief Setter for the direction
     * @param d The direction to set
     */
    void setDirection(Direction::Cardinal d);

    /**
     * @brief Setter for the hitBox (the position and size)
     * @param hb The hitbox to set
     */
    void setHitBox(const Rectangle& hb);
};

#endif // PACMAN_PACMAN_H
