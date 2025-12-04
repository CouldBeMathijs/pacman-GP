#include "LevelState.h"

#include "GameOverState.h"
#include "PausedState.h"
#include "VictoryState.h"
#include "WorldAsciiGridParser.h"
#include "WorldCreator.h"

LevelState::LevelState() : m_factory(std::make_shared<ViewCompatibleEntityFactory>()) {
    const WorldAsciiGridParser parser;
    m_world = WorldCreator::createWorld("./assets/worldmap", parser, m_factory);
}

void LevelState::update(const Direction d) {
    switch (m_world.getState()) {
    case WorldState::RUNNING:
        m_world.update(d);
        return;
    case WorldState::VICTORY:
        m_requestedPops = 1;
        m_requestedState = std::make_unique<VictoryState>(ScoreKeeper::getInstance().getLevel() + 1);
        return;
    case WorldState::GAME_OVER:
        m_requestedPops = 1;
        m_requestedState = std::make_unique<GameOverState>();
    }
}

void LevelState::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        m_requestedState = std::make_unique<PausedState>();
    }
}
