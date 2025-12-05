#ifndef PACMAN_WALL_VIEW_H
#define PACMAN_WALL_VIEW_H
#include "IEntityView.h"

class WallView final : public IEntityView {
public:
    explicit WallView(std::shared_ptr<IEntityModel>);
};

#endif
