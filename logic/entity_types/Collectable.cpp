#include "Collectable.h"

#include "Visitor.h"
void Coin::accept(IEntityVisitor& visitor) { visitor.visit(*this); }
void Fruit::accept(IEntityVisitor& visitor) { visitor.visit(*this); }