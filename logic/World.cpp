#include "World.h"

#include "AbstractEntityFactory.h"
#include "LogicConstants.h"
#include "Visitor.h"
#include "entity_types/Pacman.h"

#include <algorithm>
#include <ranges>
#include <fstream>
#include <iostream>
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

    // --- Step 1: Find Pacman and perform controlled movement/collision ---

    // Find Pacman by iterating through all entities.
    for (auto& entity_ptr : m_entities) {
        pacman = std::dynamic_pointer_cast<Pacman>(entity_ptr);
        if (pacman) {
            // Found Pacman, break the search loop
            break;
        }
        // Reset pacman to nullptr if the dynamic_cast failed for this entity
        pacman = nullptr;
    }

    // Check if Pacman was successfully found before proceeding with collision logic
    if (pacman) {
        // --- Pacman Movement and Collision Resolution ---

        pacman->setDirection(d);

        // Calculate the potential new position
        const Position current_pos = pacman->getPosition();
        Position future_pos = current_pos;
        const double current_speed = pacman->getSpeed();

        switch (d) {
            // Calculate future_pos based on direction and speed
            case Direction::SOUTH: future_pos.y += current_speed; break;
            case Direction::WEST:  future_pos.x -= current_speed; break;
            case Direction::NORTH: future_pos.y -= current_speed; break;
            case Direction::EAST:  future_pos.x += current_speed; break;
        }

        // Initialize flags BEFORE the target loop
        bool moveBlocked = false;
        bool interactionOccurred = false;

        // Define an epsilon buffer to handle floating-point imprecision and ensure slight overlap
        const double EPSILON = 0.001;

        // Use the full width/height of Pacman
        const double pacman_width = LogicConstants::ENTITY_WIDTH;
        const double pacman_height = LogicConstants::ENTITY_HEIGHT;

        // --- Bounding Box Calculation (Robust for all quadrants) ---
        // Calculate the minimum and maximum coordinates for the search area,
        // expanded by EPSILON for robust collision detection.
        const double min_x = future_pos.x - EPSILON;
        const double max_x = future_pos.x + pacman_width + EPSILON;
        const double min_y = future_pos.y - EPSILON;
        const double max_y = future_pos.y + pacman_height + EPSILON;

        // Define the search area corners (Top-Left and Bottom-Right)
        const Position search_top_left = {min_x, min_y};
        const Position search_bottom_right = {max_x, max_y};

        // Retrieve all entities potentially overlapping with the future position.
        const auto target_entities = getEntitiesInBounds(search_top_left, search_bottom_right);

        // Loop through ALL targets to determine the cumulative collision outcome (Blocking vs. Interaction).
        for (const auto& target_ptr : target_entities) {
            // Do not check collision with self
            if (target_ptr.get() == pacman.get()) continue;

            CollisionHandler handler(*pacman);
            target_ptr->accept(handler);

            const CollisionResult& result = handler.getResult();

            // CONSOLIDATE RESULTS:
            if (result.moveBlocked) {
                moveBlocked = true; // Once a block is found, the move is always blocked.
                break; // Optimization: Stop checking if movement is blocked.
            }
            if (result.interactionOccurred) {
                interactionOccurred = true; // Note if any interaction occurred.
            }
        }

        // FINAL DECISION: Apply movement and interaction outside the loop.
        if (moveBlocked) {
            // Position is NOT updated. Pacman stays at current_pos.
        } else {
            // Position is updated (even if target_entities was empty).
            pacman->setPosition(future_pos);

            if (interactionOccurred) {
                // If interaction occurred, run the pickup/game logic on ALL targets
                // that were in the future bounds.
                PickupVisitor pickup_logic;
                for (const auto& target_ptr : target_entities) {
                    if (target_ptr.get() == pacman.get()) continue;
                    target_ptr->accept(pickup_logic);
                }
            }
        }

        // Call Pacman's non-movement update (e.g., animation, base class logic)
        pacman->update(d);
    }

    // --- Step 2: Update all other entities (e.g., Ghosts, Coins, Walls, etc.) ---

    // This loop calls the simplified update on ALL entities, skipping Pacman if he was handled.
    for (const auto& entity_ptr : m_entities) {
        // If Pacman was found and updated in Step 1, skip him here.
        if (pacman && entity_ptr == pacman) continue;

        // Update all non-Pacman entities (or all entities if Pacman wasn't found).
        // The Direction 'd' is passed, but is typically ignored by non-player entities.
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