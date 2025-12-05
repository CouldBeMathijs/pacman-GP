#ifndef PACMAN_GHOST_VIEW_H
#define PACMAN_GHOST_VIEW_H
#include "IDirectionalEntityView.h"

class BlueGhostView final : public IDirectionalEntityView {
public:
    explicit BlueGhostView(std::shared_ptr<IEntityModel>);
};

class OrangeGhostView final : public IDirectionalEntityView {
public:
    explicit OrangeGhostView(std::shared_ptr<IEntityModel>);
};

class PinkGhostView final : public IDirectionalEntityView {
public:
    explicit PinkGhostView(std::shared_ptr<IEntityModel>);
};

class RedGhostView final : public IDirectionalEntityView {
public:
    explicit RedGhostView(std::shared_ptr<IEntityModel>);
};

#endif
