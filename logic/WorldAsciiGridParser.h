#ifndef PACMAN_WORLD_ASCII_GRID_PARSER_H
#define PACMAN_WORLD_ASCII_GRID_PARSER_H
#include "IWorldConfigParser.h"

#include <fstream>

class WorldAsciiGridParser final : public IWorldConfigParser {
public:
    [[nodiscard]] std::vector<std::vector<char>> parse(const std::string& filename) const override;
};

#endif
