#ifndef PACMAN_LOGICCONSTANTS_H
#define PACMAN_LOGICCONSTANTS_H
namespace LogicConstants {
constexpr unsigned int AMOUNT_OF_ENTITIES_WIDTH = 20;
constexpr unsigned int AMOUNT_OF_ENTITIES_HEIGHT = 11;
constexpr float TARGET_ASPECT_RATIO = static_cast<float>(AMOUNT_OF_ENTITIES_WIDTH) / static_cast<float>(AMOUNT_OF_ENTITIES_HEIGHT);
}
#endif // PACMAN_LOGICCONSTANTS_H
