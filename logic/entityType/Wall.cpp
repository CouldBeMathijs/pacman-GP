#include "Wall.h"

#include "Visitor.h"

Wall::Wall(const Rectangle& pos) : IEntityModel(pos, Direction::Cardinal::EAST) {}

void Wall::accept(IEntityVisitor& visitor) { visitor.visit(*this); }
