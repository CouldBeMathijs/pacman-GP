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
    std::vector<std::shared_ptr<Observer>> observers;
public:
    virtual ~Subject();
    virtual void update(Direction);
    void addObserver(std::shared_ptr<Observer>);
    virtual void accept(IEntityVisitor& visitor) = 0;
};

class EntityModel : public Subject {
protected:
    explicit EntityModel(const Position& pos, Direction d = Direction::EAST);
    Position pos;
    Direction direction;
public:
    [[nodiscard]] Position getPosition() const;
    [[nodiscard]] Direction getDirection() const;
    [[nodiscard]] bool isInBounds(const Position& topLeft, const Position& bottomRight) const;
};

#endif // PACMAN_SUBJECT_H
