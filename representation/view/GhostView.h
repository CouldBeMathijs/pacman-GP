#ifndef PACMAN_GHOST_VIEW_H
#define PACMAN_GHOST_VIEW_H
#include "IDirectionalEntityView.h"

class IGhostView : public IDirectionalEntityView {
public:
    IGhostView(Assets::TextureLocation t, std::shared_ptr<IEntityModel> e);
};

class BlueGhostView final : public IGhostView {
public:
    explicit BlueGhostView(std::shared_ptr<IEntityModel>);
};

class OrangeGhostView final : public IGhostView {
public:
    explicit OrangeGhostView(std::shared_ptr<IEntityModel>);
};

class PinkGhostView final : public IGhostView {
public:
    explicit PinkGhostView(std::shared_ptr<IEntityModel>);
};

class RedGhostView final : public IGhostView {
public:
    explicit RedGhostView(std::shared_ptr<IEntityModel>);
};

#endif
