#include "Subject.h"

Subject::~Subject() = default;
void Subject::update(Direction) {
    updateObservers();
}

void Subject::addObserver(std::shared_ptr<Observer> n) { observers.push_back(std::move(n)); }

Rectangle EntityModel::getHitBox() const {
    return hitBox;
}

Direction EntityModel::getDirection() const { return direction; }

TypeOfEntity EntityModel::getType() const { return type; }

bool EntityModel::isInBounds(const Rectangle& boundBox) const {
    const bool x_overlap = hitBox.bottomRight.x > boundBox.topLeft.x &&
                     hitBox.topLeft.x < boundBox.bottomRight.x;
    const bool y_overlap = hitBox.bottomRight.y > boundBox.topLeft.y &&
                     hitBox.topLeft.y < boundBox.bottomRight.y;
    return x_overlap && y_overlap;
}

void Subject::updateObservers() const {
    for (const auto& o : observers) {
        o->update();
    }
}

EntityModel::EntityModel(const Rectangle& hb, const Direction d, const TypeOfEntity t) : hitBox(hb), direction(d), type(t) {}
