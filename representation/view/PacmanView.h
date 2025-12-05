#ifndef PACMAN_PACMAN_VIEW_H
#define PACMAN_PACMAN_VIEW_H
#include "IDirectionalEntityView.h"

class PacmanView final : public IDirectionalEntityView {
public:
    explicit PacmanView(std::shared_ptr<IEntityModel>);
    void update() override;
};


#endif
