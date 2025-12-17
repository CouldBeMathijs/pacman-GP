#ifndef PACMAN_ENTITY_MODEL_H
#define PACMAN_ENTITY_MODEL_H
#include "ISubject.h"
#include "Position.h"

class IEntityModel : public ISubject {
protected:
    IEntityModel(Rectangle hitBox, Direction::Cardinal);
    Direction::Cardinal m_direction;
    Rectangle m_hitBox;

public:
    [[nodiscard]] Direction::Cardinal getDirection() const;
    [[nodiscard]] Rectangle getHitBox() const;
    [[nodiscard]] bool isInBounds(const Rectangle& boundBox) const;
    [[nodiscard]] bool isBlocked(const std::vector<std::shared_ptr<IEntityModel>>& touchingEntities);
    static Rectangle calculateFutureHitBox(const Rectangle& current_hb, Direction::Cardinal d, double speed);
    void snapToGrid();
};

#endif
