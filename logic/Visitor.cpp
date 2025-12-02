#include "Visitor.h"
void PacmanCollisionVisitor::visit(Ghost& target) {
    // Pacman vs Ghost: Game Over or Eat Ghost
    m_result.interactionOccurred = true;
}
void PacmanCollisionVisitor::visit(Wall& target) {
    // Pacman vs Wall: Blocked
    m_result.moveBlocked = true;
}
void PacmanCollisionVisitor::visit(Coin& target) {
    // Pacman vs Coin: Pickup interaction noted
    m_result.interactionOccurred = true;
}
void PacmanCollisionVisitor::visit(Fruit& target) {
    // Pacman vs Fruit: Pickup interaction noted
    m_result.interactionOccurred = true;
}
void GhostCollisionVisitor::visit(Ghost& target) {
    // Ghost vs Ghost logic
    m_result.moveBlocked = true;
}
void GhostCollisionVisitor::visit(Pacman& target) {
    // Ghost vs Pacman: Game Over or Run Away
    m_result.interactionOccurred = true;
    target.ghostTouches();
}
void GhostCollisionVisitor::visit(Wall& target) {
    // Ghost vs Wall: Blocked
    m_result.moveBlocked = true;
}
void CollectableVisitor::visit(Coin& coin) { coin.bePickedUp(); }
void CollectableVisitor::visit(Fruit& fruit) { fruit.bePickedUp(); }
void CollisionHandler::visit(Pacman& target) {
    CollisionResolver<Pacman> resolver(target, m_result);
    m_initiator.accept(resolver);
}
void CollisionHandler::visit(Ghost& target) {
    CollisionResolver<Ghost> resolver(target, m_result);
    m_initiator.accept(resolver);
}
void CollisionHandler::visit(Wall& target) {
    // Logic: Initiator.accept(ResolverThatHoldsWall)
    CollisionResolver<Wall> resolver(target, m_result);
    m_initiator.accept(resolver);
}
void CollisionHandler::visit(Coin& target) {
    CollisionResolver<Coin> resolver(target, m_result);
    m_initiator.accept(resolver);
}
void CollisionHandler::visit(Fruit& target) {
    CollisionResolver<Fruit> resolver(target, m_result);
    m_initiator.accept(resolver);
}
