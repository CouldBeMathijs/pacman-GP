#include "Ghost.h"

#include "Visitor.h"
void Ghost::accept(IEntityVisitor& visitor) { visitor.visit(*this); }