#ifndef PACMAN_RANDOM_H
#define PACMAN_RANDOM_H

#include <iostream>
#include <random>

/**
 * @brief Singleton class which provides all randomness
 */
class Random {
private:
    std::mt19937 m_generator;
    Random();

public:
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    static Random& getInstance();

    int generateInt(int min, int max);

    double generateDouble(double min, double max);

    template <typename T>
    const T& getRandomElement(const std::vector<T>& vec) {
            // 1. Check if the vector is empty to prevent accessing an invalid index.
            if (vec.empty()) {
                // You can throw an exception or return a default value,
                // but throwing is generally safer for a utility function.
                throw std::logic_error("Cannot get a random element from an empty vector.");
            }

            // 2. Determine the range for the index.
            // The indices are from 0 up to (size - 1).
            constexpr int minIndex = 0;
            const int maxIndex = static_cast<int>(vec.size() - 1);

            // 3. Use the existing integer generator to pick a random index.
            int randomIndex = generateInt(minIndex, maxIndex);

            // 4. Return the element at the random index.
            return vec[randomIndex];
        }
    };


#endif // PACMAN_RANDOM_H
