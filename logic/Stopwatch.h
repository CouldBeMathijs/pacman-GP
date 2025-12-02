#ifndef PACMAN_STOPWATCH_H
#define PACMAN_STOPWATCH_H

#include <chrono>
#include <thread>

constexpr float MAX_DELTA_TIME = 1.0 / 60.0;

/**
 * @brief Singeton which keeps track of time throughout the game runtime
 */
class Stopwatch {
private:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;

    double m_deltaTime;

    TimePoint m_lastTickTime;

    Stopwatch();

public:
    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;

    static Stopwatch& getInstance();

    void tick();

    [[nodiscard]] double getDeltaTime() const;
};

#endif // PACMAN_STOPWATCH_H
