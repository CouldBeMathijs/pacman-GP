#include "Collectable.h"

#include "Visitor.h"
void Collectable::bePickedUp() {
    if (!m_isPickedUp) {
        m_isPickedUp = true;
        updateObservers();
    }
}
void Collectable::update(Direction direction) {
    if (m_isPickedUp) {
        return;
    }
    EntityModel::update(direction);
}

void Coin::accept(IEntityVisitor& visitor) { visitor.visit(*this); }
void Fruit::accept(IEntityVisitor& visitor) { visitor.visit(*this); }