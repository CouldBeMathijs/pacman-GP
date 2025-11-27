#ifndef PACMAN_SCORE_H
#define PACMAN_SCORE_H
#include "Observer.h"

class ScoreKeeper final : public Observer {
private:
    unsigned int m_currentScore = 0;
public:
    explicit ScoreKeeper() = default;
    [[nodiscard]] unsigned int getScore() const;
    void update() override {};
    void addToScore(int s);
};

#endif // PACMAN_SCORE_H
