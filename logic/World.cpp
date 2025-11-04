#include "World.h"

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

World World::createWorldFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        throw std::runtime_error(filename + " was not opened successfully...");
    }

    char c;
    while (inputFile.get(c)) {

    }

    inputFile.close();

    return World();
}