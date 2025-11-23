#ifndef PACMAN_VISITOR_H
#define PACMAN_VISITOR_H
#include "Subject.h"

// --- Forward Declarations ---
// These are necessary because the Visitor knows about all Entities
class EntityModel;
class Fruit;
class Coin;
class Wall;
class Ghost;
class Pacman;

// ====================================================================
// SECTION 1: VISITOR INTERFACE (IEntityVisitor) and RESULTS
// ====================================================================

// --- Collision Result Structure ---
// Used to pass back information about the collision without relying on global state.
struct CollisionResult {
    bool moveBlocked = false;
    bool interactionOccurred = false; // e.g., Game Over, Ghost Eaten
};

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
// SECTION 2: CONCRETE OPERATION VISITORS
// ====================================================================

/**
 * @brief Visitor for handling item pickup logic (Coin, Fruit).
 * This is a simple single-dispatch operation.
 */
class PickupVisitor final : public IEntityVisitor {
public:
    void visit(Pacman& pacman) override {}
    void visit(Ghost& ghost) override {}
    void visit(Wall& wall) override {}

    void visit(Coin& coin) override {
        // Logic: Add score, remove coin from map
    }

    void visit(Fruit& fruit) override {
        // Logic: Add bonus score, remove fruit from map
    }
};

// ====================================================================
// SECTION 3: COLLISION RESOLVER VISITORS (The Second Dispatch Layer)
// These visitors contain the specific A-vs-B logic.
// ====================================================================

/**
 * @brief Handles the second half of the dispatch for Pacman collisions (Pacman vs X).
 * It is *accepted* by the Target (X).
 */
class PacmanCollisionResolver final : public IEntityVisitor {
private:
    CollisionResult& m_result;

public:
    explicit PacmanCollisionResolver(CollisionResult& result) : m_result(result) {}

    void visit(Pacman& target) override {} // Pacman vs Pacman is ignored

    void visit(Ghost& target) override {
        // Pacman vs Ghost: Game Over or Eat Ghost
        m_result.interactionOccurred = true;
        // Logic to handle game state change (e.g., Pacman::die() or Ghost::beEaten())
    }

    void visit(Wall& target) override {
        // Pacman vs Wall: Blocked
        m_result.moveBlocked = true;
    }

    // Pacman does not collide with items in the way that blocks movement
    void visit(Coin& target) override {}
    void visit(Fruit& target) override {}
};

/**
 * @brief Handles the second half of the dispatch for Ghost collisions (Ghost vs X).
 * It is *accepted* by the Target (X).
 */
class GhostCollisionResolver final : public IEntityVisitor {
private:
    CollisionResult& m_result;

public:
    explicit GhostCollisionResolver(CollisionResult& result) : m_result(result) {}

    void visit(Ghost& target) override {} // Ghost vs Ghost is ignored

    void visit(Pacman& target) override {
        // Ghost vs Pacman: Game Over or Run Away (if Pacman is powered up)
        m_result.interactionOccurred = true;
        // Logic to handle game state change (e.g., Pacman::die() or Ghost::flee())
    }

    void visit(Wall& target) override {
        // Ghost vs Wall: Blocked
        m_result.moveBlocked = true;
        // Logic to force Ghost to choose a new direction
    }

    // Ghosts ignore items in terms of blocking movement
    void visit(Coin& target) override {}
    void visit(Fruit& target) override {}
};

// ====================================================================
// SECTION 4: THE PRIMARY COLLISION VISITOR (The First Dispatch Layer)
// This visitor is *accepted* by the TARGET entity and bridges to the second layer.
// ====================================================================

/**
 * @brief The primary collision visitor. It is accepted by the TARGET entity (B).
 * It then generates the appropriate RESOLVER visitor (based on A's type)
 * and has the TARGET (B) accept the RESOLVER.
 */
class CollisionVisitor final {
private:
    EntityModel& m_initiator; // Entity A (the moving entity)
    CollisionResult m_result; // State to pass back the outcome

public:
    explicit CollisionVisitor(EntityModel& initiator) : m_initiator(initiator) {}

    // Public getter to check the result after the dispatch has completed
    [[nodiscard]] const CollisionResult& getResult() const { return m_result; }

    // --- The bridging methods (first dispatch) ---
    // These methods create the correct RESOLVER visitor based on the initiator's type (m_initiator)
    // and then call the SECOND DISPATCH on the TARGET.

    // Note: Since CollisionVisitor is NOT derived from IEntityVisitor, these methods
    // must be called manually via the movement logic or we need an intermediate class.
    // To strictly stick to the IEntityVisitor interface for the first dispatch,
    // we would need a helper class (as shown below).
};

// --- Helper Class to fit Collision Logic into IEntityVisitor (Recommended) ---
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

    // This method is called when the TARGET (B) accepts the visitor: B.accept(handler)
    void visit(Pacman& target) override {
        // B is a Pacman. Now, let the Initiator (A) resolve the A-vs-B collision.
        PacmanCollisionResolver resolver(m_result);
        m_initiator.accept(resolver); // **SECOND DISPATCH** (A.accept(Resolver))
    }

    void visit(Ghost& target) override {
        // B is a Ghost. Now, let the Initiator (A) resolve the A-vs-B collision.
        GhostCollisionResolver resolver(m_result);
        m_initiator.accept(resolver); // **SECOND DISPATCH**
    }
    /*
        void visit(Wall& target) override {
            // B is a Wall. Now, let the Initiator (A) resolve the A-vs-B collision.
            WallCollisionResolver resolver(m_result); // (You'd need a WallCollisionResolver)
            m_initiator.accept(resolver);             // **SECOND DISPATCH**
        }

        // Items should typically not block the move, so they can use a generic resolver
        void visit(Coin& target) override {
            CoinCollisionResolver resolver(m_result);
            m_initiator.accept(resolver);
        }
        void visit(Fruit& target) override {
            FruitCollisionResolver resolver(m_result);
            m_initiator.accept(resolver);
        }
    */
};

#endif // PACMAN_VISITOR_H