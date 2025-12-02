#include "Ghost.h"

#include "Visitor.h"
Ghost::Ghost(const Rectangle& pos) : EntityModel(pos, Direction::EAST) {}
void Ghost::accept(IEntityVisitor& visitor) { visitor.visit(*this); }
double Ghost::getSpeed() const { return m_speed; }
BlueGhost::BlueGhost(const Rectangle& pos) : Ghost(pos) {}
PinkGhost::PinkGhost(const Rectangle& pos) : Ghost(pos) {}
OrangeGhost::OrangeGhost(const Rectangle& pos) : Ghost(pos) {}
RedGhost::RedGhost(const Rectangle& pos) : Ghost(pos) {}