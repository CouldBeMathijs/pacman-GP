#include "Collectable.h"

#include "Visitor.h"
void Collectable::bePickedUp() {
    if (!m_isPickedUp) {
        m_isPickedUp = true;
        m_scorekeeper->addToScore(m_value);
        updateObservers();
    }
}
void Collectable::update(const Direction direction) {
    if (m_isPickedUp) {
        return;
    }
    EntityModel::update(direction);
}
void Collectable::setScoreKeeper(const std::shared_ptr<ScoreKeeper>& s) {
    m_scorekeeper = s;
}
void Collectable::setValue(const int i) { m_value = i; }
Coin::Coin(const Rectangle& pos) : Collectable(pos, Direction::EAST, COIN) {
    setValue(100);
}

void Coin::accept(IEntityVisitor& visitor) { visitor.visit(*this); }

Fruit::Fruit(const Rectangle& pos) : Collectable(pos, Direction::EAST, FRUIT) {
    setValue(200);
}
void Fruit::accept(IEntityVisitor& visitor) { visitor.visit(*this); }