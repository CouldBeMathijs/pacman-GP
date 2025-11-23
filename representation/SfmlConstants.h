#ifndef PACMAN_SFMLCONSTANTS_H
#define PACMAN_SFMLCONSTANTS_H
#include "LogicConstants.h"
namespace SfmlConstants {
constexpr float VIEW_HEIGHT = 800.0f; // A constant height for the game world
constexpr float VIEW_WIDTH = VIEW_HEIGHT * LogicConstants::TARGET_ASPECT_RATIO;
}
#endif // PACMAN_SFMLCONSTANTS_H


