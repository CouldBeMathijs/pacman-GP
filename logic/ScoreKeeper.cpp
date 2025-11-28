#include "ScoreKeeper.h"

#include <iostream>

unsigned int ScoreKeeper::getScore() const {
    return m_currentScore;
}

void ScoreKeeper::addCollectable() { m_collectablesLeft++; }

void ScoreKeeper::addToScore(const int s) {
    m_currentScore += s;
    std::cout << "Score - " << m_currentScore << " :: Collectables Left - " << m_collectablesLeft << std::endl;
}

void ScoreKeeper::removeCollectable() {
    m_collectablesLeft != 0 ? m_collectablesLeft-- : throw std::runtime_error("Cannot remove collectable, none left");
}

bool ScoreKeeper::collectablesLeft() const {
    return m_collectablesLeft != 0;
}