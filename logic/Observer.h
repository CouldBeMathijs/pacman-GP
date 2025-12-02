#ifndef PACMAN_OBSERVER_H
#define PACMAN_OBSERVER_H

class Subject;
/**
 * @brief Pure virtual base class for the observer pattern
 */
class Observer {
protected:
    Observer() = default;

public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};

#endif // PACMAN_OBSERVER_H
