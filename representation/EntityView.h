
#ifndef PACMAN_ENTITYVIEW_H
#define PACMAN_ENTITYVIEW_H
#include "Observer.h"

class EntityView : public Observer {};

class CoinView : public EntityView {};
class FruitView : public EntityView {};
class GhostView : public EntityView {};
class PacmanView : public EntityView {};
class WallView : public EntityView {};

#endif // PACMAN_ENTITYVIEW_H
