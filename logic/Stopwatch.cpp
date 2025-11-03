#include "Stopwatch.h"
Stopwatch::Stopwatch() {
    lastTickTime = Clock::now();
    deltaTime = 0.0;
}

Stopwatch& Stopwatch::getInstance() {
    static Stopwatch instance;
    return instance;
}

void Stopwatch::tick() {
    TimePoint currentTime = Clock::now();

    std::chrono::duration<double> duration = currentTime - lastTickTime;
    double rawDelta = duration.count();

    if (rawDelta < MAX_DELTA_TIME) {
        auto required_wait = std::chrono::duration<double>(MAX_DELTA_TIME - rawDelta);

        std::this_thread::sleep_for(required_wait);

        currentTime = Clock::now();
        duration = currentTime - lastTickTime;
        deltaTime = duration.count();

    } else {
        deltaTime = rawDelta;
    }

    lastTickTime = currentTime;
}

double Stopwatch::getDeltaTime() const {
    return deltaTime;
}