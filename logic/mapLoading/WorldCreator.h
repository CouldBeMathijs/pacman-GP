#ifndef PACMAN_WORLD_CREATOR_H
#define PACMAN_WORLD_CREATOR_H
#include "../World.h"

class IEntityFactory;
class IWorldConfigParser;

/**
 * @brief Purely static class, allows for generating the world_object using different IWorldConfigParsers
 */
class WorldCreator {
public:
    static World createWorld(const std::string& filename, const IWorldConfigParser& parser,
                             const std::shared_ptr<IEntityFactory>& factory);
};

#endif
