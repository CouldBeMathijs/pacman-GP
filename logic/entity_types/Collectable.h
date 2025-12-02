#ifndef PACMAN_COLLECTABLE_H
#define PACMAN_COLLECTABLE_H
#include "Subject.h"

/**
 * @brief Virtual class for all collectables
 */
class Collectable : public EntityModel {
protected:
    bool m_isPickedUp = false;
    int m_value = 0;
    explicit Collectable(const Rectangle& pos, const Direction d) : EntityModel(pos, d) {}
public:
    void bePickedUp();
    void update(Direction) override;
    void setValue(int);
};

/**
 * @brief Can be picked up by Pacman and increases the score when picked up
 */
class Coin final : public Collectable {
public:
    explicit Coin(const Rectangle& pos);
    void accept(IEntityVisitor& visitor) override;
};

/**
 * @brief Can be picked up by Pacman, increases the score and causes ghost panic when picked up
 */
class Fruit final : public Collectable {
public:
    explicit Fruit(const Rectangle& pos);
    void accept(IEntityVisitor& visitor) override;
};

#endif // PACMAN_COLLECTABLE_H
