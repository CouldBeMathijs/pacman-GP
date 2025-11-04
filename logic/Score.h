
#ifndef PACMAN_SCORE_H
#define PACMAN_SCORE_H
#include "Observer.h"

class Score final : public Observer {
    void update() override;
};

#endif // PACMAN_SCORE_H
