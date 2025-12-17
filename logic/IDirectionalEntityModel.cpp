#include "IDirectionalEntityModel.h"

IDirectionalEntityModel::IDirectionalEntityModel(const Rectangle& hitBox, const Direction::Cardinal cardinal,
                                                 const double speed)
    : IEntityModel(hitBox, cardinal), m_speed(speed) {}

void IDirectionalEntityModel::goToSpawn() { m_hitBox.moveTo(m_spawnPoint); }

double IDirectionalEntityModel::getSpeed() const { return m_speed; }

void IDirectionalEntityModel::setDirection(const Direction::Cardinal d) { m_direction = d; }