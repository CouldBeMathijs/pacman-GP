#include "WallView.h"

WallView::WallView(std::shared_ptr<IEntityModel> e)
    : IEntityView(Assets::getSpriteInfo(Assets::WallBase), std::move(e)) {}
