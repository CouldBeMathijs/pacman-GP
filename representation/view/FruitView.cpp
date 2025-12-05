#include "FruitView.h"

FruitView::FruitView(std::shared_ptr<IEntityModel> e)
    : IEntityView(Assets::getSpriteInfo(Assets::FruitBase), std::move(e)) {}

