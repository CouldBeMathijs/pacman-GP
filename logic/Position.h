#ifndef PACMAN_POSITION_H
#define PACMAN_POSITION_H
#include <iosfwd>

struct Position {
    // --- Member Variables ---
    double x;
    double y;

    // --- Constructors ---
    // Inline constructor for initialization
    Position(const double x, const double y) : x(x), y(y) {}

    // --- Assignment Operator ---
    Position& operator=(const Position& other);

    // --- Compound Assignment Operators ---
    Position& operator+=(const Position& other);
    Position& operator-=(const Position& other);

    // Component-wise multiplication/division with another Position
    Position& operator*=(const Position& other);
    Position& operator/=(const Position& other);

    // Scalar multiplication/division
    Position& operator*=(double scalar);
    Position& operator/=(double scalar);

    // --- Utility Methods ---
    [[nodiscard]] Position rescale(const Position& current_min, const Position& current_max, const Position& wanted_min,
                                   const Position& wanted_max) const;
    [[nodiscard]] double manhattan_distance_to(const Position& other) const;
};

// --- Non-Member Arithmetic Operators ---
Position operator*(const Position& lhs, const Position& rhs);
Position operator*(const Position& lhs, double scalar);
Position operator*(double scalar, const Position& rhs);
Position operator+(const Position& lhs, const Position& rhs);
Position operator-(const Position& lhs, const Position& rhs);
Position operator/(const Position& lhs, const Position& rhs);
Position operator/(const Position& lhs, double scalar);

// --- Comparison Operator ---
bool operator==(const Position& lhs, const Position& rhs);

// --- Stream Insertion Operator ---
std::ostream& operator<<(std::ostream& os, const Position& p);

struct Rectangle {
    Position topLeft;
    Position bottomRight;

    Rectangle(const Position& top_left, const Position& bottom_right);
    Rectangle();

    [[nodiscard]] Rectangle movedBy(double deltaX, double deltaY) const;
    [[nodiscard]] Rectangle rescale(const Position& current_min, const Position& current_max,
                                    const Position& wanted_min, const Position& wanted_max) const;
    [[nodiscard]] Rectangle scaledBy(double scale) const;
    [[nodiscard]] bool isCenteredOnTile(double epsilon) const;
    void moveBy(double deltaX, double deltaY);
    void moveTo(const Position& newTopLeft);
    void snapToGrid();
};

#endif // PACMAN_POSITION_H
