#ifndef PACMAN_SUBJECT_H
#define PACMAN_SUBJECT_H
#include "Direction.h"
#include "IObserver.h"

#include <memory>
#include <vector>

class IEntityVisitor;

class ISubject {
    std::vector<std::shared_ptr<IObserver>> m_observers;

public:
    virtual void accept(IEntityVisitor& visitor) = 0;
    virtual void update(Direction);
    virtual ~ISubject();
    void addObserver(std::shared_ptr<IObserver>);
    virtual void notify() const;
};

#endif // PACMAN_SUBJECT_H
