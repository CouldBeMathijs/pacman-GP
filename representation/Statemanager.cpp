#include "Statemanager.h"

#include "Camera.h"
#include "state/MenuState.h"

Statemanager::Statemanager() {
    emplace(std::make_unique<MenuState>());
}

void Statemanager::update(Direction d) {
    this->top()->update(d);
    const unsigned int requestedPops = this->top()->getRequestedPops();
    std::unique_ptr<AbstractState> stateToPush;
    if (this->top()->isRequestedState()) {
        stateToPush = (this->top()->getRequestedState());
    }
    for (unsigned int i = 0; i < requestedPops; i++) {
        pop();
    }
    if (stateToPush) {
        this->push(std::move(stateToPush));
    }
}

void Statemanager::handleInput(const sf::Event& event) {
    this->top()->handleInput(event);
}

bool Statemanager::empty() const {
    return std::stack<std::unique_ptr<AbstractState>>::empty();
}
