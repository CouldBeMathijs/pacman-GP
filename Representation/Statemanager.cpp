#include "Statemanager.h"

#include "State/MenuState.h"
Statemanager::Statemanager() {
    emplace(std::make_unique<MenuState>());
}

void Statemanager::drawScreen(sf::RenderWindow& window) {
    this->top()->drawScreen(window);
}
void Statemanager::handleInput(const sf::Event& event) {
    if (auto newState = this->top()->handleInput(event)) {
        this->push(std::move(newState));
    }
}

