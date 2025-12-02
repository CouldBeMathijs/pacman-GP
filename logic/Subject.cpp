#include "Subject.h"

#include <utility>

Subject::~Subject() = default;
void Subject::update(Direction) { updateObservers(); }

void Subject::addObserver(std::shared_ptr<Observer> n) { m_observers.push_back(std::move(n)); }

// TypeOfEntity EntityModel::getType() const { return m_type; }

void Subject::updateObservers() const {
    for (const auto& o : m_observers) {
        o->update();
    }
}
