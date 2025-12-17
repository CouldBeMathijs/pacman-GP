#ifndef PACMAN_SUBJECT_H
#define PACMAN_SUBJECT_H
#include "entityType/Direction.h"
#include "patterns/IObserver.h"

#include <memory>
#include <vector>

class IEntityVisitor;

class ISubject {
    std::vector<std::shared_ptr<IObserver>> m_observers;

public:
    virtual void accept(IEntityVisitor& visitor) = 0;
    virtual void notify() const;
    virtual void update(Direction::Cardinal);
    virtual ~ISubject();
    void addObserver(std::shared_ptr<IObserver>);
};

#endif // PACMAN_SUBJECT_H
