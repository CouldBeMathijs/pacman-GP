#ifndef PACMAN_WALL_H
#define PACMAN_WALL_H
#include "IEntityModel.h"

/**
 * @brief Blocks Pacman movement
 */
class Wall final : public IEntityModel {
public:
    explicit Wall(const Rectangle& pos);
    void accept(IEntityVisitor& visitor) override;
};

#endif // PACMAN_WALL_H
