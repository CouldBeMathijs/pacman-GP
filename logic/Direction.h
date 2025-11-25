#ifndef PACMAN_DIRECTION_H
#define PACMAN_DIRECTION_H

enum class Direction {
    EAST,
    SOUTH,
    WEST,
    NORTH,
};

/**
 * @brief Checks if two given directions are exact opposites (e.g., EAST and WEST).
 *
 * @param d1 The first direction.
 * @param d2 The second direction.
 * @return true if d1 is the opposite of d2.
 */
inline bool isOpposite(const Direction d1, const Direction d2) {
    if (d1 == d2)
        return false;

    switch (d1) {
    case Direction::EAST:
        return d2 == Direction::WEST;

    case Direction::WEST:
        return d2 == Direction::EAST;

    case Direction::NORTH:
        return d2 == Direction::SOUTH;

    case Direction::SOUTH:
        return d2 == Direction::NORTH;
    }
    return false;
}

#endif // PACMAN_DIRECTION_H