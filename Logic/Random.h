#ifndef PACMAN_RANDOM_H
#define PACMAN_RANDOM_H

#include <iostream>
#include <random>

class Random {
private:
    std::mt19937 generator;
    Random();

public:
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    static Random& getInstance();

    int generateInt(int min, int max);

    double generateDouble(double min, double max);
};
#endif // PACMAN_RANDOM_H
