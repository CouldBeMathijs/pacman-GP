#ifndef PACMAN_VISITOR_H
#define PACMAN_VISITOR_H
#include "entity_types/Collectable.h"
#include "entity_types/Ghost.h"
#include "entity_types/Pacman.h"

// --- Forward Declarations ---
class EntityModel;
class Fruit;
class Coin;
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
// SECTION 2: CONCRETE COLLISION HANDLERS (The Double Dispatch Layers)
// ====================================================================

/**
 * @brief Handles the second half of the dispatch for Pacman collisions (Pacman vs X).
 * It is *accepted* by the Target (X).
 * **Responsibility:** Set the CollisionResult flag.
 */
class PacmanCollisionVisitor final : public IEntityVisitor {
private:
    CollisionResult& m_result;

public:
    explicit PacmanCollisionVisitor(CollisionResult& result) : m_result(result) {}

    void visit(Pacman& target) override {} // Pacman vs Pacman is ignored

    void visit(Ghost& target) override {
        // Pacman vs Ghost: Game Over or Eat Ghost
        m_result.interactionOccurred = true;
        // Logic to handle Pacman::die() or Ghost::beEaten()
    }

    void visit(Wall& target) override {
        // Pacman vs Wall: Blocked
        m_result.moveBlocked = true;
    }

    void visit(Coin& target) override {
        // Pacman vs Coin: Pickup interaction noted
        m_result.interactionOccurred = true;
        // Actual pickup logic is handled by CollectableVisitor elsewhere.
    }

    void visit(Fruit& target) override {
        // Pacman vs Fruit: Pickup interaction noted
        m_result.interactionOccurred = true;
        // Actual pickup logic is handled by CollectableVisitor elsewhere.
    }
};

/**
 * @brief Handles the second half of the dispatch for Ghost collisions (Ghost vs X).
 * It is *accepted* by the Target (X).
 */
class GhostCollisionVisitor final : public IEntityVisitor {
private:
    CollisionResult& m_result;

public:
    explicit GhostCollisionVisitor(CollisionResult& result) : m_result(result) {}

    void visit(Ghost& target) override {} // Ghost vs Ghost is ignored

    void visit(Pacman& target) override {
        // Ghost vs Pacman: Game Over or Run Away
        m_result.interactionOccurred = true;
        // Logic to handle Pacman::die() or Ghost::flee()
    }

    void visit(Wall& target) override {
        // Ghost vs Wall: Blocked
        m_result.moveBlocked = true;
        // Logic to force Ghost to choose a new direction
    }

    // Ghosts ignore items in terms of blocking movement or interaction
    void visit(Coin& target) override {}
    void visit(Fruit& target) override {}
};

// ====================================================================
// SECTION 3: NEW PICKUP VISITOR
// ====================================================================

/**
 * @brief Handles the pure pickup interaction for collectable items (Pacman vs Collectable).
 * **Responsibility:** Perform the 'bePickedUp' action.
 * This visitor does not set the CollisionResult.
 */
class CollectableVisitor final : public IEntityVisitor {
public:
    // This visitor only cares about Pacman vs Collectable interactions.
    // All other visits are ignored as they are handled by the collision logic.

    void visit(Pacman& pacman) override {}
    void visit(Ghost& ghost) override {}
    void visit(Wall& wall) override {}

    void visit(Coin& coin) override {
        // Pacman is the initiator, Coin is the target: Perform Pickup
        coin.bePickedUp();
    }

    void visit(Fruit& fruit) override {
        // Pacman is the initiator, Fruit is the target: Perform Pickup
        fruit.bePickedUp();
    }
};

// ====================================================================
// SECTION 4: THE MAIN COLLISION DISPATCHER
// ====================================================================

/**
 * @brief This class acts as the true IEntityVisitor for the first dispatch.
 * When Entity B calls B.accept(CollisionHandler), this class starts the process.
 */
class CollisionHandler final : public IEntityVisitor {
private:
    EntityModel& m_initiator;
    CollisionResult m_result;

public:
    explicit CollisionHandler(EntityModel& initiator) : m_initiator(initiator) {}
    [[nodiscard]] const CollisionResult& getResult() const { return m_result; }

    // --- The bridging methods (first dispatch: Target B calls B.accept(handler)) ---

    // 1. Target B is a dynamic entity (Pacman or Ghost). We use the double dispatch.
    void visit(Pacman& target) override {
        // B is a Pacman. Let the Initiator (A) resolve the A-vs-B collision.
        PacmanCollisionVisitor resolver(m_result);
        m_initiator.accept(resolver); // **SECOND DISPATCH** (A.accept(Resolver))
    }

    void visit(Ghost& target) override {
        // B is a Ghost. Let the Initiator (A) resolve the A-vs-B collision.
        GhostCollisionVisitor resolver(m_result);
        m_initiator.accept(resolver); // **SECOND DISPATCH** (A.accept(Resolver))
    }

    // 2. Target B is a static/passive entity (Wall, Coin, Fruit).
    //    We must trigger the correct VISIT method on the RESOLVER directly.
    void visit(Wall& target) override {
        if (dynamic_cast<Pacman*>(&m_initiator)) {
            PacmanCollisionVisitor resolver(m_result);
            resolver.visit(target); // **DIRECT VISIT** -> runs PacmanCollisionVisitor::visit(Wall& target)
        } else if (dynamic_cast<Ghost*>(&m_initiator)) {
            GhostCollisionVisitor resolver(m_result);
            resolver.visit(target); // **DIRECT VISIT** -> runs GhostCollisionVisitor::visit(Wall& target)
        }
    }

    void visit(Coin& target) override {
        if (dynamic_cast<Pacman*>(&m_initiator)) {
            PacmanCollisionVisitor resolver(m_result);
            resolver.visit(target); // **DIRECT VISIT** -> runs PacmanCollisionVisitor::visit(Coin& target)
        } else if (dynamic_cast<Ghost*>(&m_initiator)) {
            GhostCollisionVisitor resolver(m_result);
            resolver.visit(target); // **DIRECT VISIT** -> runs GhostCollisionVisitor::visit(Coin& target)
        }
    }

    void visit(Fruit& target) override {
        if (dynamic_cast<Pacman*>(&m_initiator)) {
            PacmanCollisionVisitor resolver(m_result);
            resolver.visit(target); // **DIRECT VISIT** -> runs PacmanCollisionVisitor::visit(Fruit& target)
        } else if (dynamic_cast<Ghost*>(&m_initiator)) {
            GhostCollisionVisitor resolver(m_result);
            resolver.visit(target); // **DIRECT VISIT** -> runs PacmanCollisionVisitor::visit(Fruit& target)
        }
    }
};

#endif // PACMAN_VISITOR_H