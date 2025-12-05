#ifndef PACMAN_FRUIT_VIEW_H
#define PACMAN_FRUIT_VIEW_H
#include "IEntityView.h"

class FruitView final : public IEntityView {
public:
    explicit FruitView(std::shared_ptr<IEntityModel>);
};



#endif
