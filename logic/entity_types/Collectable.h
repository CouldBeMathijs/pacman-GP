#ifndef PACMAN_COLLECTABLE_H
#define PACMAN_COLLECTABLE_H
#include "ScoreKeeper.h"
#include "Subject.h"

class Collectable : public EntityModel {
protected:
    bool m_isPickedUp = false;
    std::shared_ptr<ScoreKeeper> m_scorekeeper;
    int m_value = 0;
public:
    explicit Collectable(const Rectangle& pos, const Direction d, const TypeOfEntity t) : EntityModel(pos, d, t) {}
    void bePickedUp();
    void update(Direction) override;
    void setScoreKeeper(const std::shared_ptr<ScoreKeeper>& s);
    void setValue(int);
};

class Coin final : public Collectable {
public:
    explicit Coin(const Rectangle& pos);
    void accept(IEntityVisitor& visitor) override;
};

class Fruit final : public Collectable {
public:
    explicit Fruit(const Rectangle& pos);
    void accept(IEntityVisitor& visitor) override;
};

#endif // PACMAN_COLLECTABLE_H
