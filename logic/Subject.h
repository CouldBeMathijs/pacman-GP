#ifndef PACMAN_SUBJECT_H
#define PACMAN_SUBJECT_H
#include "Observer.h"
#include "Position.h"

#include <memory>
#include <vector>

enum class Direction {
    EAST,
    SOUTH,
    WEST,
    NORTH
};

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
    [[nodiscard]] Direction getDirection() const;

protected:
    explicit EntityModel(const Position& pos) : pos(pos) {}
private:
    Position pos;
    Direction direction = Direction::WEST;
};

#endif // PACMAN_SUBJECT_H
