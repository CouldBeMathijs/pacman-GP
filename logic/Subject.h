#ifndef PACMAN_SUBJECT_H
#define PACMAN_SUBJECT_H
#include "Direction.h"
#include "Observer.h"
#include "Position.h"

#include <memory>
#include <vector>

class Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers;
public:
    virtual ~Subject();
    virtual void update(Direction);
    void addObserver(std::shared_ptr<Observer>);
};

class EntityModel : public Subject {
public:
    [[nodiscard]] Position getPosition() const;
    [[nodiscard]] Direction getDirection() const;

protected:
    explicit EntityModel(const Position& pos, Direction d = Direction::EAST);
    Position pos;
    Direction direction;
};

#endif // PACMAN_SUBJECT_H
