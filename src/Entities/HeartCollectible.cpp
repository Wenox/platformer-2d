#include "HeartCollectible.h"


HeartCollectible::HeartCollectible(sf::Vector2f position)
        : Entity{position}
{}

void HeartCollectible::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}