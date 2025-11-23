#include "World.h"

#include "AbstractEntityFactory.h"
#include "LogicConstants.h"

#include <fstream>
#include <iostream>
#include <vector>

void World::addEntity(std::shared_ptr<EntityModel> e) {
    m_entities.emplace_back(std::move(e));
}
std::vector<std::shared_ptr<EntityModel>> World::getEntities() {
    return m_entities;
}

std::vector<std::shared_ptr<EntityModel>> World::getEntitiesInBounds(Position topleft, Position bottomright) {
    std::vector<std::shared_ptr<EntityModel>> results;

    std::copy_if(
        m_entities.begin(),
        m_entities.end(),
        std::back_inserter(results), // Efficiently adds elements to the results vector
        [&topleft, &bottomright](const std::shared_ptr<EntityModel>& entity) {
            // Check if the entity (which is a shared_ptr) is not null and is in bounds.
            return entity && entity->isInBounds(topleft, bottomright);
        }
    );

    return results;
}

void World::update(Direction d) const {
    for (auto& entity : m_entities) {
        entity->update(d);
    }
}

World WorldCreator::createWorldFromFile(const std::string& filename, std::shared_ptr<AbstractEntityFactory> factory) {
    std::ifstream inputFile(filename);
    // Handeling the file
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
            Position pos = Position(x, y).rescale({0,0},
                {static_cast<double>(row_size), static_cast<double>(col_size)},
                {-1, -LogicConstants::REVERSE_TARGET_ASPECT_RATIO},
                {1, LogicConstants::REVERSE_TARGET_ASPECT_RATIO});

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