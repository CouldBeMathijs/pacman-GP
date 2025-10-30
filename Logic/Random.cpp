#include "Random.h"
Random::Random() {
    std::random_device rd;
    generator = std::mt19937(rd());
}
Random& Random::getInstance() {
    static Random instance;
    return instance;
}
int Random::generateInt(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}
double Random::generateDouble(double min, double max) {
    // Use a uniform distribution for floating-point numbers.
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}