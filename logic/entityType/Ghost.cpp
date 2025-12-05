#include "Ghost.h"

#include "Visitor.h"

IGhost::IGhost(const Rectangle& pos, const GhostMode start_mode) : IEntityModel(pos, Direction::EAST), m_currentMode(start_mode) {}

void IGhost::accept(IEntityVisitor& visitor) { visitor.visit(*this); }

double IGhost::getSpeed() const { return m_speed; }

GhostMode IGhost::getMode() const { return m_currentMode; }

BlueGhost::BlueGhost(const Rectangle& pos) : IGhost(pos, GhostMode::CHASING) {}

PinkGhost::PinkGhost(const Rectangle& pos) : IGhost(pos, GhostMode::WAITING) {}

OrangeGhost::OrangeGhost(const Rectangle& pos) : IGhost(pos, GhostMode::CHASING) {}

RedGhost::RedGhost(const Rectangle& pos) : IGhost(pos, GhostMode::WAITING) {}