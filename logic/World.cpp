#include "World.h"
#include <vector>

void World::addEntity(std::unique_ptr<EntityModel> e) {
    entities.emplace_back(std::move(e));
}
void World::update() {
    for (auto& entity : entities) {
        entity->update();
    }
}
World::World(std::string filename) {

}