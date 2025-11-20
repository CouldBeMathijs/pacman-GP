#include "Position.h"

#include <iostream>
#include <stdexcept>
/**
 * @brief Assignment operator.
 * @param other The Position to copy from.
 * @return Reference to the current Position object.
 */
Position& Position::operator=(const Position& other) {
    if (this != &other) {
        this->x = other.x;
        this->y = other.y;
    }
    return *this;
}

/**
 * @brief Compound addition operator (this += other).
 * @param other The Position to add.
 * @return Reference to the current Position object.
 */
Position& Position::operator+=(const Position& other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
}

/**
 * @brief Compound subtraction operator (this -= other).
 * @param other The Position to subtract.
 * @return Reference to the current Position object.
 */
Position& Position::operator-=(const Position& other) {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

/**
 * @brief Compound component-wise multiplication operator (this *= other).
 * @param other The Position whose components to multiply by.
 * @return Reference to the current Position object.
 */
Position& Position::operator*=(const Position& other) {
    this->x *= other.x;
    this->y *= other.y;
    return *this;
}

/**
 * @brief Compound scalar multiplication operator (this *= scalar).
 * @param scalar The scalar value to multiply by.
 * @return Reference to the current Position object.
 */
Position& Position::operator*=(double scalar) {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}

/**
 * @brief Compound component-wise division operator (this /= other).
 * @param other The Position whose components to divide by.
 * @return Reference to the current Position object.
 */
Position& Position::operator/=(const Position& other) {
    if (other.x == 0.0 || other.y == 0.0) {
        throw std::runtime_error("Cannot divide by Position with zero component in operator/=.");
    }
    this->x /= other.x;
    this->y /= other.y;
    return *this;
}

/**
 * @brief Compound scalar division operator (this /= scalar).
 * @param scalar The scalar value to divide by.
 * @return Reference to the current Position object.
 */
Position& Position::operator/=(double scalar) {
    if (scalar == 0.0) {
        throw std::runtime_error("Cannot divide Position by scalar zero in operator/=");
    }
    this->x /= scalar;
    this->y /= scalar;
    return *this;
}

// --- Utility Method Definition ---

/**
 * @brief Rescales the current Position from one range to another.
 * @param current_min The minimum bound of the current range.
 * @param current_max The maximum bound of the current range.
 * @param wanted_min The minimum bound of the desired range.
 * @param wanted_max The maximum bound of the desired range.
 * @return The rescaled Position.
 */
Position Position::rescale(const Position& current_min, const Position& current_max,
                           const Position& wanted_min, const Position& wanted_max) const {
    const Position range_current = current_max - current_min;

    // Check for zero range to prevent division by zero in the normalization step
    if (range_current.x == 0.0 && range_current.y == 0.0) {
        throw std::runtime_error("Current range has zero size.");
    }

    // Step 1: Normalize the position to a [0, 1] range
    // Normalized = (current - min) / range
    const Position normalized = (*this - current_min) / range_current;

    // Step 2: Scale the normalized position to the wanted range
    // Output = (Normalized * wanted_range) + wanted_min
    const Position range_wanted = wanted_max - wanted_min;
    const Position out = (normalized * range_wanted) + wanted_min;

    return out;
}

// --- Non-Member Operator Definitions ---

/**
 * @brief Component-wise addition operator (lhs + rhs).
 */
Position operator+(const Position& lhs, const Position& rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

/**
 * @brief Component-wise subtraction operator (lhs - rhs).
 */
Position operator-(const Position& lhs, const Position& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

/**
 * @brief Component-wise multiplication operator (lhs * rhs).
 */
Position operator*(const Position& lhs, const Position& rhs) {
    return {lhs.x * rhs.x, lhs.y * rhs.y};
}

/**
 * @brief Scalar multiplication (Position * scalar).
 */
Position operator*(const Position& lhs, double scalar) {
    return {lhs.x * scalar, lhs.y * scalar};
}

/**
 * @brief Scalar multiplication (scalar * Position).
 */
Position operator*(double scalar, const Position& rhs) {
    return {scalar * rhs.x, scalar * rhs.y};
}

/**
 * @brief Component-wise division operator (lhs / rhs).
 */
Position operator/(const Position& lhs, const Position& rhs) {
    // Check for division by zero on either component
    if (rhs.x == 0.0 || rhs.y == 0.0) {
        throw std::runtime_error("Cannot divide by Position with zero component");
    }
    return {lhs.x / rhs.x, lhs.y / rhs.y};
}

/**
 * @brief Scalar division (Position / scalar).
 */
Position operator/(const Position& lhs, double scalar) {
    if (scalar == 0.0) {
        throw std::runtime_error("Cannot divide Position by scalar zero");
    }
    return {lhs.x / scalar, lhs.y / scalar};
}

/**
 * @brief Equality comparison operator.
 */
bool operator==(const Position& lhs, const Position& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

/**
 * @brief Stream insertion operator for easy printing.
 */
std::ostream& operator<<(std::ostream& os, const Position& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}