#ifndef PACMAN_STOPWATCH_H
#define PACMAN_STOPWATCH_H

#include <chrono>
#include <thread>

#define MAX_DELTA_TIME (1.0 / 60.0)

class Stopwatch {
private:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;

    double deltaTime;

    TimePoint lastTickTime;

    Stopwatch();

public:
    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;

    static Stopwatch& getInstance();

    void tick();

    [[nodiscard]] double getDeltaTime() const;
};

#endif // PACMAN_STOPWATCH_H
