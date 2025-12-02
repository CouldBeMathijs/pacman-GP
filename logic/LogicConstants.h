#ifndef PACMAN_LOGIC_CONSTANTS_H
#define PACMAN_LOGIC_CONSTANTS_H
namespace LogicConstants {
constexpr unsigned int AMOUNT_OF_ENTITIES_WIDTH = 20;
constexpr double ENTITY_WIDTH = 1.0 / AMOUNT_OF_ENTITIES_WIDTH;
constexpr unsigned int AMOUNT_OF_ENTITIES_HEIGHT = 11;
constexpr double ENTITY_HEIGHT = 1.0 / AMOUNT_OF_ENTITIES_HEIGHT;
constexpr float TARGET_ASPECT_RATIO =
    static_cast<float>(AMOUNT_OF_ENTITIES_WIDTH) / static_cast<float>(AMOUNT_OF_ENTITIES_HEIGHT);
constexpr float REVERSE_TARGET_ASPECT_RATIO = 1 / TARGET_ASPECT_RATIO;
constexpr double BASE_SPEED = 0.005;
} // namespace LogicConstants
#endif
