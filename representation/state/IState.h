#ifndef PACMAN_ABSTRACTSTATE_H
#define PACMAN_ABSTRACTSTATE_H

#include "Direction.h"
#include <SFML/Graphics.hpp>
#include <memory>

/**
 * @brief Pure virtual class for all Game States
 */
class IState {
public:
    virtual ~IState() = default;
    virtual void update(Direction) = 0;
    virtual void handleInput(const sf::Event&) = 0;

    [[nodiscard]] unsigned int getRequestedPops() const { return m_requestedPops; }

    [[nodiscard]] bool isRequestedState() const { return m_requestedState.get(); }

    [[nodiscard]] std::unique_ptr<IState> getRequestedState() { return std::move(m_requestedState); }

protected:
    IState() = default;
    unsigned int m_requestedPops = 0;
    std::unique_ptr<IState> m_requestedState = nullptr;
};

#endif // PACMAN_ABSTRACTSTATE_H
