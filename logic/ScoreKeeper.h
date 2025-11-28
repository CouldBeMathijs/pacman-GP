#ifndef PACMAN_SCORE_H
#define PACMAN_SCORE_H
#include "Observer.h"

class ScoreKeeper final : public Observer {
private:
    unsigned int m_currentScore = 0;
    unsigned int m_collectablesLeft = 0;
    //unsigned int m_level = 1;
public:
    explicit ScoreKeeper() = default;
    [[nodiscard]] bool collectablesLeft() const;
    [[nodiscard]] unsigned int getScore() const;
    void addCollectable();
    void addToScore(int s);
    void removeCollectable();
    void update() override {}
};

#endif // PACMAN_SCORE_H
