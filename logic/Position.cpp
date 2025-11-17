#include "Position.h"

#include <iostream>
#include <stdexcept>

Position& Position::operator=(const Position& other) {
    if (this != &other) {
        this->x = other.x;
        this->y = other.y;
    }
    return *this;
}
Position Position::rescale(const Position& current_min, const Position& current_max,
                                               const Position& wanted_min, const Position& wanted_max) const {
    Position range_current = current_max - current_min;
    if (range_current.x == 0.0 && range_current.y == 0.0) {
        throw std::runtime_error("Current range has zero size.");
    }

    Position normalized = (*this - current_min) / range_current;

    Position range_wanted = wanted_max - wanted_min;
    return (normalized * range_wanted) + wanted_min;
}
Position operator+(const Position& lhs, const Position& rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}
Position operator-(const Position& lhs, const Position& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}
Position operator*(const Position& lhs, double scalar) {
    return {lhs.x * scalar, lhs.y * scalar};
}
Position operator*(double scalar, const Position& rhs) {
    return {scalar * rhs.x, scalar * rhs.y};
}
Position operator*(const Position& lhs, const Position& rhs) {
    return {lhs.x * rhs.x, lhs.y * rhs.y};
}
Position operator/(const Position& lhs, double scalar) {
    if (scalar == 0.0) {
        throw std::runtime_error("Cannot divide Position by scalar zero");
    }
    return {lhs.x / scalar, lhs.y / scalar};
}
Position operator/(const Position& lhs, const Position& rhs) {
    // Check for division by zero on either component
    if (rhs.x == 0.0 || rhs.y == 0.0) {
        throw std::runtime_error("Cannot divide by Position with zero component");
    }
    return {lhs.x / rhs.x, lhs.y / rhs.y};
}
bool operator==(const Position& lhs, const Position& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
std::ostream& operator<<(std::ostream& os, const Position& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}