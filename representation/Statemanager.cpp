#include "Statemanager.h"

#include "state/MenuState.h"
Statemanager::Statemanager() {
    emplace(std::make_unique<MenuState>());
}

void Statemanager::drawScreen(sf::RenderWindow& window) {
    this->top()->drawScreen(window);
}

void Statemanager::handleInput(const sf::Event& event) {
    unsigned int amountOfPops = 0;
    if (auto newState = this->top()->handleInput(event, amountOfPops)) {
        this->push(std::move(newState));
    }
}
