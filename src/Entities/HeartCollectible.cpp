/** @file */

#include "HeartCollectible.h"


HeartCollectible::HeartCollectible(sf::Vector2f position)
        : Entity{position}
{}

void HeartCollectible::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

bool HeartCollectible::wasCollected() const {
    return collected;
}

void HeartCollectible::setCollected(bool status) {
    collected = status;
}