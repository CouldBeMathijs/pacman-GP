#include "Subject.h"
Subject::~Subject() = default;
void Subject::update(Direction) {
    for (const auto& o : observers) {
        o->update();
    }
}

void Subject::addObserver(std::shared_ptr<Observer> n) { observers.push_back(std::move(n)); }

Position EntityModel::getPosition() const {
    return pos;
}

Direction EntityModel::getDirection() const { return direction; }

bool EntityModel::isInBounds(const Position& topLeft, const Position& bottomRight) const {
    const double minX = std::min(topLeft.x, bottomRight.x);
    const double maxX = std::max(topLeft.x, bottomRight.x);
    const double minY = std::min(topLeft.y, bottomRight.y);
    const double maxY = std::max(topLeft.y, bottomRight.y);

    // Check if the entity's X coordinate is within the bounding box's X range
    const bool x_in_bounds = (pos.x >= minX && pos.x <= maxX);

    // Check if the entity's Y coordinate is within the bounding box's Y range
    const bool y_in_bounds = (pos.y >= minY && pos.y <= maxY);

    // The entity is in bounds only if both conditions are true.
    return x_in_bounds && y_in_bounds;
}

EntityModel::EntityModel(const Position& pos, const Direction d, const TypeOfEntity t) : pos(pos), direction(d), type(t) {}
