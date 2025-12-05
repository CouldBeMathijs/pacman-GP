#ifndef PACMAN_COIN_VIEW_H
#define PACMAN_COIN_VIEW_H
#include "IEntityView.h"

class CoinView final : public IEntityView {
public:
    explicit CoinView(std::shared_ptr<IEntityModel>);
};

#endif
