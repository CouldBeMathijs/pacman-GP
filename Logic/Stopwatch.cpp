#include "Stopwatch.h"
Stopwatch::Stopwatch() {
    // Initialize lastTickTime to the current time point.
    lastTickTime = Clock::now();
    deltaTime = 0.0;
}
Stopwatch& Stopwatch::getInstance() {
    static Stopwatch instance;
    return instance;
}
void Stopwatch::tick() {
    TimePoint currentTime = Clock::now();

    // Calculate the raw duration since the last tick.
    std::chrono::duration<double> duration = currentTime - lastTickTime;
    double rawDelta = duration.count();

    // Cap the frame rate to ensure consistent minimum delta time (maximum FPS).
    // This prevents the game from using an extremely small delta if the device is fast.
    if (rawDelta < MAX_DELTA_TIME) {
        // Wait until the required time for the MAX_DELTA_TIME has passed.
        std::chrono::duration<double> required_wait = std::chrono::duration<double>(MAX_DELTA_TIME - rawDelta);

        // Use std::this_thread::sleep_for to wait
        std::this_thread::sleep_for(required_wait);

        // Recalculate time after sleeping
        currentTime = Clock::now();
        duration = currentTime - lastTickTime;
        deltaTime = duration.count();

    } else {
        // No cap needed, use the calculated raw delta
        deltaTime = rawDelta;
    }

    // Update the lastTickTime for the *next* calculation.
    lastTickTime = currentTime;
}
double Stopwatch::getDeltaTime() const {
    // Return a copy, as deltaTime is a class member updated by tick().
    return deltaTime;
}