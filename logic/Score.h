#ifndef PACMAN_SCORE_H
#define PACMAN_SCORE_H
#include "Observer.h"

class Score final : public Observer {
private:
    unsigned int m_currentScore = 0;
public:
    void update() override;
};

#endif // PACMAN_SCORE_H
