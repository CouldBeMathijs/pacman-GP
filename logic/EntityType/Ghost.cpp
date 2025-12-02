#include "Ghost.h"

#include "Visitor.h"
void Ghost::accept(IEntityVisitor& visitor) { visitor.visit(*this); }
double Ghost::getSpeed() const { return m_speed; }