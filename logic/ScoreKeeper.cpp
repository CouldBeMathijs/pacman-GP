#include "ScoreKeeper.h"

#include <iostream>

unsigned int ScoreKeeper::getScore() const { return m_currentScore; }
void ScoreKeeper::removeLife() { m_lives--; }

unsigned int ScoreKeeper::getLives() const { return m_lives; }
void ScoreKeeper::addCollectable() { m_collectablesLeft++; }

void ScoreKeeper::addToScore(const int s) { m_currentScore += s; }

void ScoreKeeper::removeCollectable() {
    m_collectablesLeft != 0 ? m_collectablesLeft-- : throw std::runtime_error("Cannot remove collectable, none left");
}
void ScoreKeeper::nextLevel() { m_level++; }
unsigned int ScoreKeeper::getLevel() const { return m_level; }
void ScoreKeeper::reset() {
    m_collectablesLeft = 0;
    m_currentScore = 0;
    m_level = 0;
    m_lives = 3;
}

ScoreKeeper& ScoreKeeper::getInstance() {
    static ScoreKeeper instance;
    return instance;
}

bool ScoreKeeper::collectablesLeft() const { return m_collectablesLeft != 0; }