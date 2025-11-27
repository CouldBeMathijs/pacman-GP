#ifndef PACMAN_ABSTRACTSTATE_H
#define PACMAN_ABSTRACTSTATE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Direction.h"

class AbstractState {
public:
    virtual ~AbstractState() = default;
    virtual void update(Direction) = 0;
    virtual void handleInput(const sf::Event&) = 0;
    [[nodiscard]] unsigned int getRequestedPops() const { return m_requestedPops; }
    [[nodiscard]] bool isRequestedState() const { return m_requestedState.get(); }
    [[nodiscard]] std::unique_ptr<AbstractState> getRequestedState() { return std::move(m_requestedState); }
protected:
    AbstractState() = default;
    unsigned int m_requestedPops = 0;
    std::unique_ptr<AbstractState> m_requestedState = nullptr;
};

#endif // PACMAN_ABSTRACTSTATE_H
