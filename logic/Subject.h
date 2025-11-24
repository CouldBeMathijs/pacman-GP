#ifndef PACMAN_SUBJECT_H
#define PACMAN_SUBJECT_H
#include "Direction.h"
#include "Observer.h"
#include "Position.h"

#include <memory>
#include <vector>

class IEntityVisitor;

enum TypeOfEntity {
    PACMAN,
    GHOST,
    WALL,
    COIN,
    FRUIT,
    BROKEN
};

class Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers;
public:
    virtual ~Subject();
    virtual void update(Direction);
    void addObserver(std::shared_ptr<Observer>);
    virtual void accept(IEntityVisitor& visitor) = 0;
    void updateObservers() const;
};

class EntityModel : public Subject {
protected:
    EntityModel(const Rectangle& hitBox, Direction, TypeOfEntity t);
    Rectangle hitBox;
    Direction direction;
    const TypeOfEntity type;
public:
    [[nodiscard]] Rectangle getHitBox() const;
    [[nodiscard]] Direction getDirection() const;
    [[nodiscard]] TypeOfEntity getType() const;
    [[nodiscard]] bool isInBounds(const Rectangle& boundBox) const;
};

#endif // PACMAN_SUBJECT_H
