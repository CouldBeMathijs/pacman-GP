#ifndef PACMAN_SCOREKEEPER_H
#define PACMAN_SCOREKEEPER_H
#include "Observer.h"

#include <chrono>
/**
 * @brief Singleton which keeps all persistent score variables
 */
class ScoreKeeper final : public Observer {
private:
    // --- Chrono Definitions ---
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;

    // --- Member Variables ---
    unsigned int m_currentScore = 0;
    unsigned int m_collectablesLeft = 0;
    unsigned int m_level = 0;
    unsigned int m_lives = 3;
    TimePoint m_lastPickupTime; // Stores the time of the last pickup

    // Constant for the multiplier decay time
    static constexpr double MAX_MULTIPLIER_TIME_S = 3.0;

    ScoreKeeper();

public:
    ScoreKeeper(const ScoreKeeper&) = delete;
    ScoreKeeper& operator=(const ScoreKeeper&) = delete;
    static ScoreKeeper& getInstance();

    [[nodiscard]] bool collectablesLeft() const;
    [[nodiscard]] unsigned int getLevel() const;
    [[nodiscard]] unsigned int getLives() const;
    [[nodiscard]] unsigned int getScore() const;
    void addCollectable();
    void addPointsWithMultiplier(unsigned int baseScore);
    void addToScore(int s);
    void nextLevel();
    void removeCollectable();
    void removeLife();
    void reset();
    void update() override {}
};

#endif