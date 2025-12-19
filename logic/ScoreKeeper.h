#ifndef PACMAN_SCOREKEEPER_H
#define PACMAN_SCOREKEEPER_H

#include "patterns/IObserver.h"
#include <chrono>
#include <iomanip>
#include <vector>

struct HighScoreEntry {
    unsigned int score;
    std::time_t timestamp;

    bool operator>(const HighScoreEntry& other) const { return score > other.score; }
};

inline std::string formatTimestamp(const std::time_t t) {
    const std::tm* tm_ptr = std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(tm_ptr, "%Y-%m-%d %H:%M");
    return ss.str();
}

/**
 * @brief Singleton which keeps all persistent score variables
 */
class ScoreKeeper final : public IObserver {
    // --- Chrono Definitions ---
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;

    // --- Member Variables ---
    TimePoint m_lastDeductionTime;
    TimePoint m_lastPickupTime;
    const std::string m_filePath = "./assets/.highscores";
    std::vector<HighScoreEntry> m_highScores;
    unsigned int m_collectablesLeft = 0;
    unsigned int m_currentScore = 0;
    unsigned int m_level = 1;
    unsigned int m_lives = 3;

    // --- Constants ---
    static constexpr double MAX_MULTIPLIER_TIME_S = 3.0;
    static constexpr double TIME_BETWEEN_SCORE_DECREASE_S = 0.5;
    static constexpr int MAX_HIGH_SCORES = 5;

    ScoreKeeper();

public:
    // --- Singleton requirements ---
    ScoreKeeper(const ScoreKeeper&) = delete;
    ScoreKeeper& operator=(const ScoreKeeper&) = delete;

    const std::vector<HighScoreEntry>& getHighScores() { return m_highScores; };

    static ScoreKeeper& getInstance();

    [[nodiscard]] bool collectablesLeft() const;
    void loadHighScores();
    void saveHighScores() const;
    void recordCurrentScore();
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
    void update() override;
};

#endif
