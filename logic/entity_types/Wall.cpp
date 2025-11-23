#include "Wall.h"

#include "Visitor.h"
Wall::Wall(const Position& pos) : EntityModel(pos) {}
void Wall::accept(IEntityVisitor& visitor) { visitor.visit(*this); }
