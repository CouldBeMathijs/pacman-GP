#include "Subject.h"

#include "LogicConstants.h"
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

TypeOfEntity EntityModel::getType() const { return type; }

bool EntityModel::isInBounds(const Position& topLeft, const Position& bottomRight) const {
    constexpr double entity_width = LogicConstants::ENTITY_WIDTH;
    constexpr double entity_height = LogicConstants::ENTITY_HEIGHT;

    // --- 1. Define the Bounding Box (Search Area) ---
    // Ensure min/max values are correct regardless of input order
    const double box_minX = std::min(topLeft.x, bottomRight.x);
    const double box_maxX = std::max(topLeft.x, bottomRight.x);
    const double box_minY = std::min(topLeft.y, bottomRight.y);
    const double box_maxY = std::max(topLeft.y, bottomRight.y);


    const double entity_minX = this->pos.x - entity_width * 7/8; // Left edge
    const double entity_maxX = this->pos.x + entity_width * 15/8; // Right edge
    const double entity_minY = this->pos.y;             // Top edge (no change)
    const double entity_maxY = this->pos.y + entity_height; // Bottom edge (no change)

    // --- 3. AABB Intersection Check ---
    // The two boxes intersect (overlap) if and only if they overlap on all axes.

    // Check for X-axis overlap:
    // They DON'T overlap if the entity's right edge (entity_maxX) is to the left of the box's left edge (box_minX)
    // OR if the entity's left edge (entity_minX) is to the right of the box's right edge (box_maxX).
    const bool x_overlap = (entity_maxX > box_minX) && (entity_minX < box_maxX);

    // Check for Y-axis overlap:
    // They DON'T overlap if the entity's bottom edge (entity_maxY) is above the box's top edge (box_minY)
    // OR if the entity's top edge (entity_minY) is below the box's bottom edge (box_maxY).
    const bool y_overlap = (entity_maxY > box_minY) && (entity_minY < box_maxY);

    // The entity is in bounds (i.e., overlaps with the bounding box) only if both overlaps are true.
    return x_overlap && y_overlap;
}

EntityModel::EntityModel(const Position& pos, const Direction d, const TypeOfEntity t) : pos(pos), direction(d), type(t) {}
