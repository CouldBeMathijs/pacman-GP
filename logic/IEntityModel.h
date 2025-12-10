#ifndef PACMAN_ENTITY_MODEL_H
#define PACMAN_ENTITY_MODEL_H
#include "ISubject.h"
#include "Position.h"

class IEntityModel : public ISubject {
protected:
    IEntityModel(Rectangle hitBox, Direction);
    Direction m_direction;
    Rectangle m_hitBox;

public:
    [[nodiscard]] Direction getDirection() const;
    [[nodiscard]] Rectangle getHitBox() const;
    [[nodiscard]] bool isInBounds(const Rectangle& boundBox) const;
    static Rectangle calculateFutureHitBox(const Rectangle& current_hb, Direction d, double speed);
    void snapToGrid();
};

#endif
