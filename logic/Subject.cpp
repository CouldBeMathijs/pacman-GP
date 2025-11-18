#include "Subject.h"
Subject::~Subject() = default;
void Subject::update() {
    for (const auto& o : observers) {
        o->update();
    }
}

void Subject::addObserver(std::shared_ptr<Observer> n) { observers.push_back(std::move(n)); }

Position EntityModel::getPosition() const {
    return pos;
}