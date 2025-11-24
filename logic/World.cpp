#include "World.h"

#include "AbstractEntityFactory.h"
#include "LogicConstants.h"
#include "Visitor.h"
#include "entity_types/Pacman.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>

void World::addEntity(std::shared_ptr<EntityModel> e) { m_entities.emplace_back(std::move(e)); }
std::vector<std::shared_ptr<EntityModel>> World::getEntities() { return m_entities; }

std::vector<std::shared_ptr<EntityModel>> World::getEntitiesInBounds(Position topLeft, Position bottomRight) {
    std::vector<std::shared_ptr<EntityModel>> results;

    std::ranges::copy_if(m_entities,
                         std::back_inserter(results), // Efficiently adds elements to the results vector
                         [&topLeft, &bottomRight](const std::shared_ptr<EntityModel>& entity) {
                             // Check if the entity (which is a shared_ptr) is not null and is in bounds.
                             return entity && entity->isInBounds(topLeft, bottomRight);
                         });

    return results;
}

/**
 * @brief Updates the state of the game world, handling Pacman's movement,
 * collision resolution, interactions (like picking up pellets), and
 * the updates of all other entities.
 * * This method performs a two-step update:
 * 1. Controlled update for Pacman: calculates potential movement, performs collision
 * checks against obstacles (Walls) and interactions against consumables (Pellets, PowerPills),
 * and applies the final movement and interaction effects.
 * 2. Simplified update for all other entities (Ghosts, consumables, etc.),
 * allowing them to execute their own movement/game logic.
 * * @param d The direction input received from the user for Pacman's intended movement.
 */
void World::update(Direction d) {
    std::shared_ptr<Pacman> pacman = nullptr;

    // --- Step 1: Find Pacman and set his direction ---

    // Find Pacman (Optimized search: use a dedicated member variable in a real project)
    for (auto& entity_ptr : m_entities) {
        if ((pacman = std::dynamic_pointer_cast<Pacman>(entity_ptr))) {
            break;
        }
    }

    if (pacman) {
        pacman->setDirection(d);

        // --- Calculate Potential Future Position ---
        const Position current_pos = pacman->getPosition();
        Position future_pos = current_pos;
        const double current_speed = pacman->getSpeed();

        switch (d) {
            case Direction::SOUTH: future_pos.y += current_speed; break;
            case Direction::WEST:  future_pos.x -= current_speed; break;
            case Direction::NORTH: future_pos.y -= current_speed; break;
            case Direction::EAST:  future_pos.x += current_speed; break;
        }

        // --- Collision Search Setup ---
        bool moveBlocked = false; // Flag to determine if movement is allowed.
        constexpr double EPSILON = 0.001; // For robust floating-point comparison
        constexpr double pacman_width = LogicConstants::ENTITY_WIDTH;
        constexpr double pacman_height = LogicConstants::ENTITY_HEIGHT;

        // Bounding Box Calculation for the search area
        const double min_x = future_pos.x - EPSILON;
        const double max_x = future_pos.x + pacman_width + EPSILON;
        const double min_y = future_pos.y - EPSILON;
        const double max_y = future_pos.y + pacman_height + EPSILON;

        const Position search_top_left = {min_x, min_y};
        const Position search_bottom_right = {max_x, max_y};

        // Get all entities potentially overlapping with the future position.
        const auto target_entities = getEntitiesInBounds(search_top_left, search_bottom_right);

        // --- Collision Resolution Loop ---
        // This loop handles BOTH movement blocking AND interaction/pickup logic.
        for (const auto& target_ptr : target_entities) {
            // Do not check collision with self
            if (target_ptr.get() == pacman.get()) continue;

            // 1. Initiate Double Dispatch: Target (B) accepts the handler
            CollisionHandler handler(*pacman);
            target_ptr->accept(handler); // This triggers the A-vs-B logic inside the visitors.

            const CollisionResult& result = handler.getResult();

            // CONSOLIDATE RESULTS:
            if (result.moveBlocked) {
                moveBlocked = true;
                // Optimization: Stop checking if movement is blocked.
                // Interactions will be implicitly blocked if movement is stopped.
                break;
            }
            // Note: If interactionOccurred is true, the *actual* game state change
            // (e.g., scoring, removal of item, death) is assumed to have occurred
            // directly within the PacmanCollisionVisitor::visit() methods.
        }

        // --- FINAL DECISION: Apply Movement ---
        if (!moveBlocked) {
            // Position is updated.
            pacman->setPosition(future_pos);
        }

        // Call Pacman's non-movement update (e.g., animation, power-up timers)
        pacman->update(d);
    }

    // --- Step 2: Update all other entities (e.g., Ghosts, Coins, Walls, etc.) ---

    // This loop calls the simplified update on ALL entities.
    for (const auto& entity_ptr : m_entities) {
        // If Pacman was found and updated in Step 1, skip him here.
        if (pacman && entity_ptr == pacman) continue;

        // Update all non-Pacman entities.
        entity_ptr->update(d);
    }
}

World WorldCreator::createWorldFromFile(const std::string& filename,
                                        const std::shared_ptr<AbstractEntityFactory>& factory) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        throw std::runtime_error(filename + " was not opened successfully...");
    }

    std::vector<std::vector<char>> gridData;
    std::string line;

    while (std::getline(inputFile, line)) {
        std::vector<char> row;

        for (char c : line) {
            row.push_back(c);
        }
        gridData.push_back(std::move(row));
    }

    inputFile.close();

    size_t row_size = gridData[0].size();
    for (const auto& row : gridData) {
        if (row_size != row.size()) {
            throw std::runtime_error("Invalid world map; every line must have the same number of characters");
        }
    }
    // Building the world object
    World out;
    size_t col_size = gridData.size();
    for (size_t x = 0; x < row_size; x++) {
        for (size_t y = 0; y < col_size; y++) {
            Position pos = Position(x, y).rescale(
                {0, 0}, {static_cast<double>(row_size), static_cast<double>(col_size)},
                {-1, -LogicConstants::REVERSE_TARGET_ASPECT_RATIO}, {1, LogicConstants::REVERSE_TARGET_ASPECT_RATIO});

            switch (gridData[y][x]) {
            case '#':
                out.addEntity(factory->createWall(pos));
                break;
            case '*':
                out.addEntity(factory->createCoin(pos));
                break;
            case 'F':
                out.addEntity(factory->createFruit(pos));
                break;
            case 'P':
                out.addEntity(factory->createPacman(pos));
                break;
            case '1':
                out.addEntity(factory->createBlueGhost(pos));
                break;
            case '2':
                out.addEntity(factory->createPinkGhost(pos));
                break;
            case '3':
                out.addEntity(factory->createOrangeGhost(pos));
                break;
            case '4':
                out.addEntity(factory->createRedGhost(pos));
                break;
            default:
                break;
            }
        }
    }

    return out;
}