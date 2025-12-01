#ifndef PACMAN_VISITOR_H
#define PACMAN_VISITOR_H

#include "entity_types/Collectable.h"
#include "entity_types/Ghost.h"
#include "entity_types/Pacman.h"

// --- Forward Declarations ---
class EntityModel;
class Fruit;
class Wall;
class Ghost;
class Pacman;

/**
 * @brief Used to pass back information about the collision.
 */
struct CollisionResult {
    bool moveBlocked = false;
    bool interactionOccurred = false; // e.g., Game Over, Ghost Eaten, Item Picked Up
};

/**
 * @brief The core Visitor Interface for all dispatch layers.
 */
class IEntityVisitor {
public:
    virtual ~IEntityVisitor() = default;

    // A visit method for every concrete element type
    virtual void visit(Pacman& pacman) = 0;
    virtual void visit(Ghost& ghost) = 0;
    virtual void visit(Wall& wall) = 0;
    virtual void visit(Coin& coin) = 0;
    virtual void visit(Fruit& fruit) = 0;
};

// ====================================================================
// SECTION 2: CONCRETE COLLISION HANDLERS (The Logic Layers)
// ====================================================================

/**
 * @brief Handles logic when PACMAN is the initiator.
 */
class PacmanCollisionVisitor final : public IEntityVisitor {
private:
    CollisionResult& m_result;

public:
    explicit PacmanCollisionVisitor(CollisionResult& result) : m_result(result) {}

    void visit(Pacman& target) override {} // Pacman vs Pacman ignored

    void visit(Ghost& target) override {
        // Pacman vs Ghost: Game Over or Eat Ghost
        m_result.interactionOccurred = true;
    }

    void visit(Wall& target) override {
        // Pacman vs Wall: Blocked
        m_result.moveBlocked = true;
    }

    void visit(Coin& target) override {
        // Pacman vs Coin: Pickup interaction noted
        m_result.interactionOccurred = true;
    }

    void visit(Fruit& target) override {
        // Pacman vs Fruit: Pickup interaction noted
        m_result.interactionOccurred = true;
    }
};

/**
 * @brief Handles logic when GHOST is the initiator.
 */
class GhostCollisionVisitor final : public IEntityVisitor {
private:
    CollisionResult& m_result;

public:
    explicit GhostCollisionVisitor(CollisionResult& result) : m_result(result) {}

    void visit(Ghost& target) override { m_result.moveBlocked = true; } // Ghost vs Ghost logic

    void visit(Pacman& target) override {
        // Ghost vs Pacman: Game Over or Run Away
        m_result.interactionOccurred = true;
        target.ghostTouches();
    }

    void visit(Wall& target) override {
        // Ghost vs Wall: Blocked
        m_result.moveBlocked = true;
    }

    // Ghosts ignore items
    void visit(Coin& target) override {}
    void visit(Fruit& target) override {}
};

// ====================================================================
// SECTION 3: NEW PICKUP VISITOR
// ====================================================================

class CollectableVisitor final : public IEntityVisitor {
public:
    void visit(Pacman& pacman) override {}
    void visit(Ghost& ghost) override {}
    void visit(Wall& wall) override {}

    void visit(Coin& coin) override { coin.bePickedUp(); }

    void visit(Fruit& fruit) override { fruit.bePickedUp(); }
};

// ====================================================================
// SECTION 4: HELPER DISPATCHER (The "Glue" to remove dynamic_cast)
// ====================================================================

/**
 * @brief A temporary Visitor used to resolve the Initiator's type.
 * * It holds a reference to the TARGET.
 * We pass this visitor to the INITIATOR.
 * When the INITIATOR calls visit(InitiatorType), we finally know both types:
 * 1. The InitiatorType (via the function called)
 * 2. The TargetType (via the member variable)
 */
template <typename TargetType>
class CollisionResolver final : public IEntityVisitor {
private:
    TargetType& m_target;
    CollisionResult& m_result;

public:
    CollisionResolver(TargetType& target, CollisionResult& res) : m_target(target), m_result(res) {}

    // 1. If the Initiator identifies itself as Pacman:
    void visit(Pacman& initiator) override {
        // Create the logic handler for Pacman...
        PacmanCollisionVisitor logic(m_result);
        // ...and apply it to the specific target we are holding.
        logic.visit(m_target);
    }

    // 2. If the Initiator identifies itself as Ghost:
    void visit(Ghost& initiator) override {
        // Create the logic handler for Ghost...
        GhostCollisionVisitor logic(m_result);
        // ...and apply it to the specific target we are holding.
        logic.visit(m_target);
    }

    // The Initiator in this game is usually dynamic (Pacman/Ghost),
    // so it is unlikely a Wall will be the Initiator, but we must implement the interface.
    void visit(Wall& wall) override {}
    void visit(Coin& coin) override {}
    void visit(Fruit& fruit) override {}
};

// ====================================================================
// SECTION 5: THE MAIN COLLISION DISPATCHER
// ====================================================================

class CollisionHandler final : public IEntityVisitor {
private:
    EntityModel& m_initiator;
    CollisionResult m_result;

public:
    explicit CollisionHandler(EntityModel& initiator) : m_initiator(initiator) {}
    [[nodiscard]] const CollisionResult& getResult() const { return m_result; }

    // --- The bridging methods ---
    // Instead of casting, we create a specific Resolver for the Target,
    // and ask the Initiator to accept it.

    void visit(Pacman& target) override {
        CollisionResolver<Pacman> resolver(target, m_result);
        m_initiator.accept(resolver);
    }

    void visit(Ghost& target) override {
        CollisionResolver<Ghost> resolver(target, m_result);
        m_initiator.accept(resolver);
    }

    void visit(Wall& target) override {
        // Logic: Initiator.accept(ResolverThatHoldsWall)
        CollisionResolver<Wall> resolver(target, m_result);
        m_initiator.accept(resolver);
    }

    void visit(Coin& target) override {
        CollisionResolver<Coin> resolver(target, m_result);
        m_initiator.accept(resolver);
    }

    void visit(Fruit& target) override {
        CollisionResolver<Fruit> resolver(target, m_result);
        m_initiator.accept(resolver);
    }
};

#endif // PACMAN_VISITOR_H