#include "CoinView.h"

CoinView::CoinView(std::shared_ptr<IEntityModel> e)
    : IEntityView(Assets::getSpriteInfo(Assets::CoinBase), std::move(e)) {}
