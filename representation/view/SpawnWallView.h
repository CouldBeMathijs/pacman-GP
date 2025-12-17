#ifndef PACMAN_SPAWN_WALL_VIEW_H
#define PACMAN_SPAWN_WALL_VIEW_H
#include "IEntityView.h"

class SpawnWallView final : public IEntityView {
public:
    explicit SpawnWallView(const std::shared_ptr<IEntityModel>& entity_model);
};

#endif
