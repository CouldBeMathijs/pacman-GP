#include "ScoreKeeper.h"

#include <iostream>

unsigned int ScoreKeeper::getScore() const { return m_currentScore; }
void ScoreKeeper::addToScore(const int s) {
    std::cout << m_currentScore << std::endl;
    m_currentScore += s;
}