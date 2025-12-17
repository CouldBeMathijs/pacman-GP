#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "IDirectionalEntityModel.h"

/**
 * @brief The player character
 */
class Pacman final : public IDirectionalEntityModel {
    bool m_ghostTouch = false;
    bool m_isDying = false;

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

    void goToSpawn() override;

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
     * @brief Makes it so hasTouchedGhost() returns false until ghostTouches() is called
     */
    void resetGhostTouch();
};

#endif // PACMAN_PACMAN_H
