#ifndef PACMAN_SUBJECT_H
#define PACMAN_SUBJECT_H
#include "Direction.h"
#include "Observer.h"
#include "Position.h"

#include <memory>
#include <vector>

class IEntityVisitor;

class Subject {
private:
    std::vector<std::shared_ptr<Observer>> m_observers;

public:
    virtual void accept(IEntityVisitor& visitor) = 0;
    virtual void update(Direction);
    virtual ~Subject();
    void addObserver(std::shared_ptr<Observer>);
    void updateObservers() const;
};



#endif // PACMAN_SUBJECT_H
