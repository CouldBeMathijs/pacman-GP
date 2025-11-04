#ifndef PACMAN_SUBJECT_H
#define PACMAN_SUBJECT_H
#include "Observer.h"

#include <memory>
#include <utility>
#include <vector>

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
    std::vector<std::unique_ptr<Observer>> observers;
public:
    virtual ~Subject();
    virtual void update();
    void addObserver(std::unique_ptr<Observer>);
};

class EntityModel : public Subject {
protected:
    explicit EntityModel(Position pos) : pos(std::move(pos)) {}
private:
    Position pos;
};

#endif // PACMAN_SUBJECT_H
