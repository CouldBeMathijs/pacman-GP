#include "World.h"

#include "AbstractEntityFactory.h"

#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>

void World::addEntity(std::unique_ptr<EntityModel> e) {
    entities.emplace_back(std::move(e));
}

void World::update() const {
    for (const auto& entity : entities) {
        entity->update();
    }
}

World World::createWorldFromFile(const std::string& filename, std::shared_ptr<AbstractEntityFactory> factory) {
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

    int row_size = static_cast<int>(gridData[0].size());
    for (const auto& row : gridData) {
        if (row_size != static_cast<int>(row.size())) {
            throw std::runtime_error("Invalid world map; every line must have the same number of characters");
        }
    }

    World out;
    int col_size = static_cast<int>(gridData.size());
    for (auto x : std::ranges::views::iota(0, col_size - 1)) {
        for (auto y : std::ranges::views::iota(0, row_size - 1)) {
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
            default:
                break;
            }
        }
    }

    return out;
}