#include "World.h"

#include "AbstractEntityFactory.h"

#include <fstream>
#include <iostream>
#include <vector>

void World::addEntity(std::unique_ptr<EntityModel> e) {
    entities.emplace_back(std::move(e));
}

void World::update() const {
    for (const auto& entity : entities) {
        entity->update();
    }
}

World World::createWorldFromFile(const std::string& filename, const std::shared_ptr<AbstractEntityFactory>& factory) {
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
    for (size_t x = 0; x < col_size - 1; x++) {
        for (size_t y = 0; y < row_size - 1; y++) {
            Position pos = Position(x, y).rescale({0,0},{static_cast<double>(row_size - 1), static_cast<double>(col_size - 1)}, {-1, -1}, {1, 1});

            char c = gridData[x][y];
            switch (c) {
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
            case '2':
            case '3':
            case '4':
                out.addEntity(factory->createGhost(pos));
                break;
            default:
                break;
            }
        }
    }

    return out;
}