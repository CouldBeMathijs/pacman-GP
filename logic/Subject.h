#ifndef PACMAN_SUBJECT_H
#define PACMAN_SUBJECT_H
#include "Observer.h"
#include "Position.h"

#include <memory>
#include <vector>

class Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers;
public:
    virtual ~Subject();
    virtual void update();
    void addObserver(std::shared_ptr<Observer>);
};

class EntityModel : public Subject {
public:
    [[nodiscard]] Position getPosition() const;
protected:
    explicit EntityModel(const Position& pos) : pos(pos) {}
private:
    Position pos;
};

#endif // PACMAN_SUBJECT_H
