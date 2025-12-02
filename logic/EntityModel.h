
#ifndef PACMAN_ENTITYMODEL_H
#define PACMAN_ENTITYMODEL_H
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


#endif // PACMAN_ENTITYMODEL_H
