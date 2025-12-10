
#include "IEntityModel.h"

Rectangle IEntityModel::getHitBox() const { return m_hitBox; }

Direction IEntityModel::getDirection() const { return m_direction; }

IEntityModel::IEntityModel(Rectangle hitBox, const Direction d) : m_direction(d), m_hitBox(std::move(hitBox)) {}

bool IEntityModel::isInBounds(const Rectangle& boundBox) const {
    const bool x_overlap = m_hitBox.bottomRight.x > boundBox.topLeft.x && m_hitBox.topLeft.x < boundBox.bottomRight.x;
    const bool y_overlap = m_hitBox.bottomRight.y > boundBox.topLeft.y && m_hitBox.topLeft.y < boundBox.bottomRight.y;
    return x_overlap && y_overlap;
}

Rectangle IEntityModel::calculateFutureHitBox(const Rectangle& current_hb, const Direction d, const double speed) {
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

void IEntityModel::snapToGrid() { m_hitBox.snapToGrid(); }
