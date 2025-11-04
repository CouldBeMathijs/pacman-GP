
#ifndef PACMAN_POSITION_H
#define PACMAN_POSITION_H
#include <iosfwd>

struct Position {
    double x;
    double y;

    // Constructor with default arguments
    Position(double x, double y) : x(x), y(y) {}

    // Assignment operator (was already correctly defined inside)
    Position& operator=(const Position& other);

    // Rescale method (uses the non-member operators defined below)
    [[nodiscard]] Position rescale(const Position& current_min, const Position& current_max, const Position& wanted_min,
                     const Position& wanted_max) const;
};

Position operator*(const Position& lhs, const Position& rhs);
Position operator*(const Position& lhs, double scalar);
Position operator*(double scalar, const Position& rhs);
Position operator+(const Position& lhs, const Position& rhs);
Position operator-(const Position& lhs, const Position& rhs);
Position operator/(const Position& lhs, const Position& rhs);
Position operator/(const Position& lhs, double scalar);
bool operator==(const Position& lhs, const Position& rhs);
std::ostream& operator<<(std::ostream& os, const Position& p);

#endif // PACMAN_POSITION_H
