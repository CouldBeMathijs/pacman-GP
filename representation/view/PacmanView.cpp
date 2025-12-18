#include "PacmanView.h"

#include "entityType/Pacman.h"

PacmanView::PacmanView(std::shared_ptr<IEntityModel> e)
    : IDirectionalEntityView(Assets::getSpriteInfo(Assets::SpriteDefinition::PacmanBase), std::move(e), 3) {}

void PacmanView::update() {
    if (std::static_pointer_cast<Pacman>(getCoupledEntity())->isDying()) {
        return;
    }
    IDirectionalEntityView::update();
}
