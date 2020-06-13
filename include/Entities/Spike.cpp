#include "Spike.h"

Spike::Spike(Obj::Entity spikeType, sf::Vector2f position)
        : Entity{position}, spikeType{spikeType}
{}

void Spike::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}