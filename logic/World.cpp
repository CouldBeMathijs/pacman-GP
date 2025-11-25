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

std::vector<std::shared_ptr<EntityModel>> World::getEntitiesInBounds(const Rectangle& boundBox) {
    std::vector<std::shared_ptr<EntityModel>> results;

    std::ranges::copy_if(m_entities,
                         std::back_inserter(results), // Efficiently adds elements to the results vector
                         [&boundBox](const std::shared_ptr<EntityModel>& entity) {
                             // Check if the entity (which is a shared_ptr) is not null and is in bounds.
                             return entity && entity->isInBounds(boundBox);
                         });

    return results;
}

/**
 * @brief Updates the state of the game world, handling Pacman's movement,
 * collision resolution, interactions (like picking up pellets), and
 * the updates of all other entities.
 *
 * @param d The direction input received from the user for Pacman's intended movement.
 */
void World::update(Direction d) {
    std::shared_ptr<Pacman> pacman = nullptr;

    // --- 1. Find Pacman and set his direction ---
    for (auto& entity_ptr : m_entities) {
        if ((pacman = std::dynamic_pointer_cast<Pacman>(entity_ptr))) {
            break;
        }
    }

    if (pacman) {
        // --- NEW STEP 1.5: Direction Change Pre-Check (4-Step Lookahead) ---

        // Only perform the lookahead check if the proposed direction 'd' is different
        // from the current direction.
        if (const Direction current_direction = pacman->getDirection(); d != current_direction) {
            const double current_speed = pacman->getSpeed() * 10.0;
            const Rectangle hitBox = pacman->getHitBox().scaledBy(0.99);

            // Calculate the position after the lookahead distance in the *new* direction 'd'.
            Rectangle future_hb_check = hitBox;
            switch (d) {
            case Direction::SOUTH:
                // Move the rectangle down (positive Y)
                future_hb_check.moveBy(0.0, current_speed);
                break;

            case Direction::WEST:
                // Move the rectangle left (negative X)
                future_hb_check.moveBy(-current_speed, 0.0);
                break;

            case Direction::NORTH:
                // Move the rectangle up (negative Y)
                future_hb_check.moveBy(0.0, -current_speed);
                break;

            case Direction::EAST:
                // Move the rectangle right (positive X)
                future_hb_check.moveBy(current_speed, 0.0);
                break;
            }

            // Define the bounding box for the lookahead position.
            bool lookaheadBlocked = false;

            // Check for blocking entities (like walls) at the lookahead position.
            for (const auto blocking_targets = getEntitiesInBounds(future_hb_check);
                 const auto& target_ptr : blocking_targets) {
                if (target_ptr.get() == pacman.get()) continue;

                // Use CollisionHandler to check for a *blocking* collision.
                CollisionHandler handler(*pacman);
                target_ptr->accept(handler);

                if (handler.getResult().moveBlocked) {
                    lookaheadBlocked = true;
                    break;
                }
            }

            // If the lookahead is blocked, *REJECT* the new direction 'd'.
            if (lookaheadBlocked) {
                // Keep the current direction for the movement in step 3.
                d = current_direction;
                // Note: The original 'd' (the user input) is now ignored for this update.
            }
        }

        // Set the (potentially modified) direction for the rest of the update
        pacman->setDirection(d);

        const Rectangle current_hb = pacman->getHitBox();
        const double current_speed = pacman->getSpeed();

        // --- 2. Interaction/Pickup Search (At Current Position) ---
        // ... (Original Code for Interaction Check) ...
        {
            // Define the bounding box at the CURRENT position for interaction checks.
            const auto interaction_targets = getEntitiesInBounds(current_hb);

            for (const auto& target_ptr : interaction_targets) {
                if (target_ptr.get() == pacman.get()) continue;

                // Handle the interaction (e.g., Pacman eats a Pellet, or touches a Ghost)
                CollisionHandler handler(*pacman);
                target_ptr->accept(handler);
            }
        }

        // --- 3. Calculate Potential Future Position ---
        Rectangle future_hb = current_hb;

        // The direction 'd' here is the direction set in the NEW STEP 1.5
        switch (d) {
        case Direction::SOUTH:
            // Move the rectangle down (positive Y)
            future_hb.moveBy(0.0, current_speed);
            break;

        case Direction::WEST:
            // Move the rectangle left (negative X)
            future_hb.moveBy(-current_speed, 0.0);
            break;

        case Direction::NORTH:
            // Move the rectangle up (negative Y)
            future_hb.moveBy(0.0, -current_speed);
            break;

        case Direction::EAST:
            // Move the rectangle right (positive X)
            future_hb.moveBy(current_speed, 0.0);
            break;
        }

        // --- 4. Movement Blocking Search (At Future Position) ---
        bool moveBlocked = false;
        const auto search_future_hb = future_hb.scaledBy(0.99);

        // Collision Resolution Loop (Movement Block Only)
        for (const auto blocking_targets = getEntitiesInBounds(search_future_hb);
             const auto& target_ptr : blocking_targets) {
            if (target_ptr.get() == pacman.get()) continue;

            // Use the CollisionHandler specifically to check for *blocking* entities (like walls).
            CollisionHandler handler(*pacman);
            target_ptr->accept(handler);
            const CollisionResult& result = handler.getResult();

            if (result.moveBlocked) {
                moveBlocked = true;
                break; // Stop checking if movement is blocked.
            }
        }

        // --- 5. FINAL DECISION: Apply Movement ---
        if (!moveBlocked) {
            // Position is updated.
            pacman->setHitBox(future_hb);
        }

        // Call Pacman's non-movement update (e.g., animation, power-up timers)
        pacman->update(d);
    }

    // --- 6. Update all other entities (e.g., Ghosts, Coins, Walls, etc.) ---
    for (const auto& entity_ptr : m_entities) {
        if (pacman && entity_ptr == pacman) continue; // Skip Pacman

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

    // 1. Read the file into gridData (Correct: gridData[row][column])
    while (std::getline(inputFile, line)) {
        std::vector<char> row;
        for (char c : line) {
            row.push_back(c);
        }
        gridData.push_back(std::move(row));
    }

    inputFile.close();

    // Ensure the map is not empty
    if (gridData.empty() || gridData[0].empty()) {
        throw std::runtime_error("World map is empty.");
    }

    // 2. Define dimensions clearly
    size_t num_rows_y = gridData.size();       // Y-dimension (height)
    size_t num_cols_x = gridData[0].size();    // X-dimension (width)

    // 3. Validate map consistency
    for (const auto& row : gridData) {
        if (num_cols_x != row.size()) {
            throw std::runtime_error("Invalid world map; every line must have the same number of characters");
        }
    }

    // Building the world object
    World out;

    // 4. Loop in the standard [Y][X] order (Row by Row, then Column by Column)
    for (size_t y = 0; y < num_rows_y; y++) { // Loop over rows (Y coordinate)
        for (size_t x = 0; x < num_cols_x; x++) { // Loop over columns (X coordinate)

            // Step A: Calculate the top-left corner of the current grid cell (x, y)
            // This represents the start of the cell.
            Position pos_start = Position(static_cast<double>(x), static_cast<double>(y)).rescale(
                {0, 0}, {static_cast<double>(num_cols_x), static_cast<double>(num_rows_y)},
                {-1, -LogicConstants::REVERSE_TARGET_ASPECT_RATIO},
                {1, LogicConstants::REVERSE_TARGET_ASPECT_RATIO});

            // Step B: Calculate the bottom-right corner of the current grid cell (x+1, y+1)
            // This represents the end of the cell.
            Position pos_end = Position(static_cast<double>(x + 1), static_cast<double>(y + 1)).rescale(
                {0, 0}, {static_cast<double>(num_cols_x), static_cast<double>(num_rows_y)},
                {-1, -LogicConstants::REVERSE_TARGET_ASPECT_RATIO},
                {1, LogicConstants::REVERSE_TARGET_ASPECT_RATIO});

            // Hitbox (hb) spans the entire grid cell (100% size) for ALL entities,
            // ensuring they are all the same size relative to the grid.
            Rectangle hb = {pos_start, pos_end};
            Rectangle hb_coin = hb.scaledBy(0.2);

            // Access the grid using [row][column] which is [y][x]
            switch (gridData[y][x]) {
            case '#':
                out.addEntity(factory->createWall(hb));
                break;
            case '*':
                out.addEntity(factory->createCoin(hb_coin));
                break;
            case 'F':
                out.addEntity(factory->createFruit(hb));
                break;
            case 'P':
                out.addEntity(factory->createPacman(hb));
                break;
            case '1':
                out.addEntity(factory->createBlueGhost(hb));
                break;
            case '2':
                out.addEntity(factory->createPinkGhost(hb));
                break;
            case '3':
                out.addEntity(factory->createOrangeGhost(hb));
                break;
            case '4':
                out.addEntity(factory->createRedGhost(hb));
                break;
            default:
                // Do nothing for empty space ' '
                break;
            }
        }
    }

    return out;
}