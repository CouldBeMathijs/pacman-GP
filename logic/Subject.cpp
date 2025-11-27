#include "Subject.h"

#include <utility>

Subject::~Subject() = default;
void Subject::update(Direction) {
    updateObservers();
}

void Subject::addObserver(std::shared_ptr<Observer> n) { m_observers.push_back(std::move(n)); }

Rectangle EntityModel::getHitBox() const {
    return m_hitBox;
}

Direction EntityModel::getDirection() const { return m_direction; }

TypeOfEntity EntityModel::getType() const { return m_type; }

bool EntityModel::isInBounds(const Rectangle& boundBox) const {
    const bool x_overlap = m_hitBox.bottomRight.x > boundBox.topLeft.x &&
                     m_hitBox.topLeft.x < boundBox.bottomRight.x;
    const bool y_overlap = m_hitBox.bottomRight.y > boundBox.topLeft.y &&
                     m_hitBox.topLeft.y < boundBox.bottomRight.y;
    return x_overlap && y_overlap;
}

void Subject::updateObservers() const {
    for (const auto& o : m_observers) {
        o->update();
    }
}

EntityModel::EntityModel(Rectangle  hb, const Direction d, const TypeOfEntity t) : m_hitBox(std::move(hb)), m_direction(d), m_type(t) {}

Rectangle EntityModel::calculateFutureHitBox(const Rectangle& current_hb, const Direction d, const double speed) {
    Rectangle future_hb = current_hb;

    switch (d) {
    case Direction::SOUTH:
        // Move the rectangle down (positive Y)
        future_hb.moveBy(0.0, speed);
        break;

    case Direction::WEST:
        // Move the rectangle left (negative X)
        future_hb.moveBy(-speed, 0.0);
        break;

    case Direction::NORTH:
        // Move the rectangle up (negative Y)
        future_hb.moveBy(0.0, -speed);
        break;

    case Direction::EAST:
        // Move the rectangle right (positive X)
        future_hb.moveBy(speed, 0.0);
        break;
        // Assuming other directions (like NONE) result in no movement.
    default:
        break;
    }

    return future_hb;
}
