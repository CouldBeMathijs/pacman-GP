#ifndef PACMAN_OBSERVER_H
#define PACMAN_OBSERVER_H

class Subject;
class Observer {
protected:
    Observer() = default;

public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};

#endif // PACMAN_OBSERVER_H
