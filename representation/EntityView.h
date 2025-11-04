
#ifndef PACMAN_ENTITYVIEW_H
#define PACMAN_ENTITYVIEW_H
#include "Observer.h"

class EntityView : public Observer {};

class PacmanView : EntityView {};

class GhostView : EntityView {};

class CoinView : EntityView {};

class FruitView : EntityView {};

class WallView : EntityView {};

#endif // PACMAN_ENTITYVIEW_H
