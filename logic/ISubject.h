#ifndef PACMAN_SUBJECT_H
#define PACMAN_SUBJECT_H
#include "entityType/Direction.h"
#include "patterns/IObserver.h"

#include <memory>
#include <vector>

class IEntityVisitor;

class ISubject {
    std::vector<std::weak_ptr<IObserver>> m_observers;

public:
    virtual void accept(IEntityVisitor& visitor) = 0;
    virtual void notify();
    virtual void update(Direction::Cardinal);
    virtual ~ISubject();
    void addObserver(std::weak_ptr<IObserver>);
};

#endif // PACMAN_SUBJECT_H
