#include "Block.h"


Block::Block(sf::Vector2f position)
    : Entity{position}
{}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}