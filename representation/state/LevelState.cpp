#include "LevelState.h"

#include "GameOverState.h"
#include "PausedState.h"
#include "VictoryState.h"

LevelState::LevelState() : m_factory(std::make_shared<ConcreteEntityFactory>()) {
    m_world = WorldCreator::createWorldFromFile("./assets/testworldmap", m_factory);
}

void LevelState::update(const Direction d) {
    switch (m_world.getState()) {
    case RUNNING:
        m_world.update(d);
        return;
    case VICTORY:
        m_requestedPops = 1;
        m_requestedState = std::make_unique<VictoryState>(ScoreKeeper::getInstance().getLevel() + 1);
        return;
    case GAME_OVER:
        m_requestedPops = 1;
        m_requestedState = std::make_unique<GameOverState>();
    }
}

void LevelState::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        m_requestedState = std::make_unique<PausedState>();
    }
}
