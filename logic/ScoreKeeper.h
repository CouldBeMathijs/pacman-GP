#ifndef PACMAN_SCORE_H
#define PACMAN_SCORE_H
#include "Observer.h"

class ScoreKeeper final : public Observer {
private:
    unsigned int m_currentScore = 0;
    unsigned int m_collectablesLeft = 0;
    unsigned int m_level = 0;
    ScoreKeeper() = default;

public:
    ScoreKeeper(const ScoreKeeper&) = delete;
    ScoreKeeper& operator=(const ScoreKeeper&) = delete;
    static ScoreKeeper& getInstance();

    [[nodiscard]] bool collectablesLeft() const;
    [[nodiscard]] unsigned int getLevel() const;
    [[nodiscard]] unsigned int getScore() const;
    void addCollectable();
    void addToScore(int s);
    void nextLevel();
    void removeCollectable();
    void reset();
    void update() override {}
};

#endif // PACMAN_SCORE_H