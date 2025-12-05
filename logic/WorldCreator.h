#ifndef PACMAN_WORLD_CREATOR_H
#define PACMAN_WORLD_CREATOR_H
#include "World.h"

class IEntityFactory;
class IWorldConfigParser;

class WorldCreator {
public:
    // Takes the parser strategy as an argument
    static World createWorld(const std::string& filename, const IWorldConfigParser& parser,
                             const std::shared_ptr<IEntityFactory>& factory);
};

#endif
