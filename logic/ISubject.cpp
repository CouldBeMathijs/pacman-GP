#include "ISubject.h"

#include <utility>

ISubject::~ISubject() = default;

void ISubject::update(Direction) { notify(); }

void ISubject::addObserver(std::shared_ptr<IObserver> n) { m_observers.push_back(std::move(n)); }

void ISubject::notify() const {
    for (const auto& o : m_observers) {
        o->update();
    }
}
