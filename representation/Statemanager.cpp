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
    auto newState = this->top()->handleInput(event, amountOfPops);
    for (unsigned int i = 0; i < amountOfPops; i++) {
        pop();
    }
    if (newState) {
        this->push(std::move(newState));
    }
}
bool Statemanager::empty() const {
    return std::stack<std::unique_ptr<AbstractState>>::empty();
}
