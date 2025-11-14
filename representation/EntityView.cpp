
#include "EntityView.h"
#include <utility>

EntityView::EntityView(std::vector<sf::Sprite> m) : m_sprites(std::move(m)){}

void EntityView::update() {}

CoinView::CoinView() {
    EntityView();
}
FruitView::FruitView() {
    EntityView();
}