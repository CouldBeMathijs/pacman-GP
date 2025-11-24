#include "Collectable.h"

#include "Visitor.h"
void Collectable::bePickedUp() {
    if (!isPickedUp) {
        isPickedUp = true;
        updateObservers();
    }
}
void Collectable::update(Direction direction) {
    if (isPickedUp) {
        return;
    }
    EntityModel::update(direction);
}

void Coin::accept(IEntityVisitor& visitor) { visitor.visit(*this); }
void Fruit::accept(IEntityVisitor& visitor) { visitor.visit(*this); }