#ifndef PACMAN_I_DIRECTIONAL_ENTITY_MODEL_H
#define PACMAN_I_DIRECTIONAL_ENTITY_MODEL_H
#include "IEntityModel.h"

class IDirectionalEntityModel : public IEntityModel {
protected:
    Position m_spawnPoint = getHitBox().topLeft;
    double m_speed;
public:
    IDirectionalEntityModel(const Rectangle& hitBox, Direction::Cardinal cardinal, double speed);
    virtual void goToSpawn();

    void setDirection(Direction::Cardinal d);
};

#endif
