/** @file */

#include "Life.h"

Life::Life(sf::Vector2f position)
    : Entity{position}
{}

void Life::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}