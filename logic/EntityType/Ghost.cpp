#include "Ghost.h"

#include "Visitor.h"
AbstractGhost::AbstractGhost(const Rectangle& pos) : IEntityModel(pos, Direction::EAST) {}
void AbstractGhost::accept(IEntityVisitor& visitor) { visitor.visit(*this); }
double AbstractGhost::getSpeed() const { return m_speed; }
BlueGhost::BlueGhost(const Rectangle& pos) : AbstractGhost(pos) {}
PinkGhost::PinkGhost(const Rectangle& pos) : AbstractGhost(pos) {}
OrangeGhost::OrangeGhost(const Rectangle& pos) : AbstractGhost(pos) {}
RedGhost::RedGhost(const Rectangle& pos) : AbstractGhost(pos) {}