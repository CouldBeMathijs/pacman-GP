#include "Wall.h"

#include "Visitor.h"
Wall::Wall(const Position& pos) : EntityModel(pos, Direction::EAST, WALL) {}
void Wall::accept(IEntityVisitor& visitor) { visitor.visit(*this); }
