#include "Statemanager.h"
Statemanager::Statemanager() {
    emplace(std::make_unique<MenuState>());
}