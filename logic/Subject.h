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
    std::vector<std::shared_ptr<Observer>> m_observers;

public:
    virtual void accept(IEntityVisitor& visitor) = 0;
    virtual void update(Direction);
    virtual ~Subject();
    void addObserver(std::shared_ptr<Observer>);
    void updateObservers() const;
};

class EntityModel : public Subject {
protected:
    EntityModel(Rectangle hitBox, Direction);
    Direction m_direction;
    Rectangle m_hitBox;
    // const TypeOfEntity m_type;

public:
    [[nodiscard]] Direction getDirection() const;
    [[nodiscard]] Rectangle getHitBox() const;
    //[[nodiscard]] TypeOfEntity getType() const;
    [[nodiscard]] bool isInBounds(const Rectangle& boundBox) const;
    static Rectangle calculateFutureHitBox(const Rectangle& current_hb, Direction d, double speed);
};

#endif // PACMAN_SUBJECT_H
