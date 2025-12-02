#ifndef PACMAN_STOPWATCH_H
#define PACMAN_STOPWATCH_H

#include <chrono>
#include <thread>

constexpr float MAX_DELTA_TIME = 1.0 / 60.0;

/**
 * @brief Singleton which keeps track of time throughout the game runtime
 */
class Stopwatch {
private:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;

    TimePoint m_lastTickTime;
    double m_deltaTime;

    Stopwatch();

public:
    // -- Deleted constructors
    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;

    /**
     * @brief Singleton getter method
     * @return The one and only Camera instance
     */
    static Stopwatch& getInstance();

    /**
     * @brief ticks deltaTime and makes sure the game runs at 1/MAX_DELTA_TIME fps
     */
    void tick();

    /**
     * @brief Getter for deltaTime
     * @return the current deltaTime, set after the last tick()
     */
    [[nodiscard]] double getDeltaTime() const;
};

#endif // PACMAN_STOPWATCH_H
