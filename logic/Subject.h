#ifndef PACMAN_SUBJECT_H
#define PACMAN_SUBJECT_H
#include "Direction.h"
#include "Observer.h"
#include "Position.h"

#include <memory>
#include <vector>

class IEntityVisitor;

enum TypeOfEntity { PACMAN, GHOST, WALL, COIN, FRUIT, BROKEN };

class Subject {
private:
    std::vector<std::shared_ptr<Observer>> m_observers;

public:
    virtual ~Subject();
    virtual void update(Direction);
    void addObserver(std::shared_ptr<Observer>);
    virtual void accept(IEntityVisitor& visitor) = 0;
    void updateObservers() const;
};

class EntityModel : public Subject {
protected:
    EntityModel(Rectangle hitBox, Direction, TypeOfEntity t);
    Rectangle m_hitBox;
    Direction m_direction;
    const TypeOfEntity m_type;

public:
    [[nodiscard]] Rectangle getHitBox() const;
    [[nodiscard]] Direction getDirection() const;
    [[nodiscard]] TypeOfEntity getType() const;
    [[nodiscard]] bool isInBounds(const Rectangle& boundBox) const;
    static Rectangle calculateFutureHitBox(const Rectangle& current_hb, Direction d, double speed);
};

#endif // PACMAN_SUBJECT_H
