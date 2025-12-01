#include "Collectable.h"

#include "Visitor.h"
void Collectable::bePickedUp() {
    if (!m_isPickedUp) {
        auto& score = ScoreKeeper::getInstance();
        m_isPickedUp = true;
        score.addToScore(m_value);
        score.removeCollectable();
        updateObservers();
    }
}

void Collectable::update(const Direction direction) {
    if (m_isPickedUp) {
        return;
    }
    EntityModel::update(direction);
}

void Collectable::setValue(const int i) { m_value = i; }

Coin::Coin(const Rectangle& pos) : Collectable(pos, Direction::EAST, COIN) {
    setValue(10);
}

void Coin::accept(IEntityVisitor& visitor) { visitor.visit(*this); }

Fruit::Fruit(const Rectangle& pos) : Collectable(pos, Direction::EAST, FRUIT) {
    setValue(20);
}

void Fruit::accept(IEntityVisitor& visitor) { visitor.visit(*this); }
