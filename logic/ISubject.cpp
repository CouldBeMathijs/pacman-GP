#include "ISubject.h"

#include <utility>

ISubject::~ISubject() = default;

void ISubject::update(Direction) { updateObservers(); }

void ISubject::addObserver(std::shared_ptr<Observer> n) { m_observers.push_back(std::move(n)); }

void ISubject::updateObservers() const {
    for (const auto& o : m_observers) {
        o->update();
    }
}
