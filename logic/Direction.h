#ifndef PACMAN_DIRECTION_H
#define PACMAN_DIRECTION_H
namespace Direction {
/**
 * @brief The order of the Directions is the same as the order in the Spritemap
 */
enum class Cardinal {
    EAST,
    SOUTH,
    WEST,
    NORTH,
    NONE,
};

/**
 * @brief Checks if two given directions are exact opposites.
 *
 * @param d1 The first direction.
 * @param d2 The second direction.
 * @return true if d1 is the opposite of d2.
 */
constexpr bool isOpposite(const Cardinal d1, const Direction::Cardinal d2) {
    if (d1 == d2)
        return false;

    switch (d1) {
    case Cardinal::EAST:
        return d2 == Cardinal::WEST;

    case Cardinal::WEST:
        return d2 == Cardinal::EAST;

    case Cardinal::NORTH:
        return d2 == Cardinal::SOUTH;

    case Cardinal::SOUTH:
        return d2 == Cardinal::NORTH;

    case Cardinal::NONE:
        return false;
    }
    return false;
}

constexpr Cardinal getOpposite(const Cardinal d) {
    switch (d) {
    case Cardinal::EAST:
        return Cardinal::WEST;
    case Cardinal::SOUTH:
        return Cardinal::NORTH;
    case Cardinal::WEST:
        return Cardinal::EAST;
    case Cardinal::NORTH:
        return Cardinal::SOUTH;
    case Cardinal::NONE:
        break;
    }
    return Cardinal::NONE;
}
}
#endif // PACMAN_DIRECTION_H