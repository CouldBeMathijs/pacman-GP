#include "World.h"
void World::update() {
    for (auto& entity : entities) {
        entity.update();
    }
}