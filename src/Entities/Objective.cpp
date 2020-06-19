/** @file */

#include "Objective.h"


Objective::Objective(sf::Vector2f position)
    : Entity{position}
{}

void Objective::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}