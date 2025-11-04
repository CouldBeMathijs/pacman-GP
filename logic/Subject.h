#ifndef PACMAN_SUBJECT_H
#define PACMAN_SUBJECT_H
#include "Observer.h"

#include <memory>
#include <utility>

struct Position : public std::pair<double, double> {
public:
    double x = first;
    double y = second;
    Position(const double x, const double y) {
        first = x;
        second = y;
    }
};

class Subject {
private:
    std::unique_ptr<Observer> observer;
public:
    virtual ~Subject();
    virtual void update();
    void addObserver(std::unique_ptr<Observer>);
};

class EntityModel : public Subject {
protected:
    explicit EntityModel(Position  pos) : pos(std::move(pos)) {}
private:
    Position pos;

};

#endif // PACMAN_SUBJECT_H
