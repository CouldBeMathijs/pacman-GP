#include "World.h"

#include "AbstractEntityFactory.h"
#include "LogicConstants.h"
#include "Visitor.h"
#include "entity_types/Pacman.h"
#include "entity_types/Wall.h"

#include <algorithm>
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

void World::update(Direction d) {
    std::shared_ptr<Pacman> pacman = nullptr;

    // --- Step 1: Find Pacman and perform controlled movement/collision ---

    // Find Pacman and store a pointer. We do this in a separate loop for clarity.
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
            // Calculate future_pos based on direction and speed...
            case Direction::SOUTH: future_pos.y += current_speed; break;
            case Direction::WEST:  future_pos.x -= current_speed; break;
            case Direction::NORTH: future_pos.y -= current_speed; break;
            case Direction::EAST:  future_pos.x += current_speed; break;
        }

        // Initialize flags BEFORE the target loop
        bool moveBlocked = false;
        bool interactionOccurred = false;

        // Get the entities (B) in the movement path.
        const auto target_entities = getEntitiesInBounds(future_pos * 0.9999999999,
            future_pos + Position{1/LogicConstants::AMOUNT_OF_ENTITIES_WIDTH, 1/LogicConstants::AMOUNT_OF_ENTITIES_HEIGHT});

        // Loop through ALL targets to determine the cumulative collision outcome.
        for (const auto& target_ptr : target_entities) {
            // Do not check collision with self

            if (target_ptr.get() == pacman.get()) continue;

            CollisionHandler handler(*pacman);
            target_ptr->accept(handler);

            const CollisionResult& result = handler.getResult();

            // CONSOLIDATE RESULTS:
            if (result.moveBlocked) {
                moveBlocked = true; // Once a block is found, the move is always blocked.
                break;
            }
            if (result.interactionOccurred) {
                interactionOccurred = true; // Note if any interaction occurred.
            }
        }

        // FINAL DECISION: Apply movement and interaction outside the loop.
        if (moveBlocked) {
            // Position is NOT updated.
        } else {
            // Position is updated (even if target_entities was empty).
            pacman->setPosition(future_pos);

            if (interactionOccurred) {
                // If interaction occurred, run the pickup/game logic on ALL targets.
                PickupVisitor pickup_logic;
                for (const auto& target_ptr : target_entities) {
                    if (target_ptr.get() == pacman.get()) continue;
                    target_ptr->accept(pickup_logic);
                }
            }
        }

        // Call Pacman's non-movement update (e.g., animation, base class)
        pacman->update(d);
    }

    // --- Step 2: Update all other entities (e.g., Ghosts, Coins, Walls, etc.) ---

    // This loop calls the simplified update on ALL entities, skipping Pacman if he was handled.
    for (const auto& entity_ptr : m_entities) {
        // If Pacman was found and updated in Step 1, skip him here.
        if (pacman && entity_ptr == pacman) continue;

        // Update all non-Pacman entities (or all entities if Pacman wasn't found).
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