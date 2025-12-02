#ifndef PACMAN_ENTITY_MODEL_H
#define PACMAN_ENTITY_MODEL_H
#include "Position.h"
#include "Subject.h"

class EntityModel : public Subject {
protected:
    EntityModel(Rectangle hitBox, Direction);
    Direction m_direction;
    Rectangle m_hitBox;

public:
    [[nodiscard]] Direction getDirection() const;
    [[nodiscard]] Rectangle getHitBox() const;
    [[nodiscard]] bool isInBounds(const Rectangle& boundBox) const;
    static Rectangle calculateFutureHitBox(const Rectangle& current_hb, Direction d, double speed);
};

#endif
