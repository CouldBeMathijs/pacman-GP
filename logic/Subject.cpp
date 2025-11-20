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

EntityModel::EntityModel(const Position& pos, const Direction d) : pos(pos), direction(d) {}
