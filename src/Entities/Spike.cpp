#include "Spike.h"


Spike::Spike(Obj::Entity spikeType, sf::Vector2f position)
        : Entity{position}, spikeType{spikeType}
{}

void Spike::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Spike::setTextureDirection() {
    switch (spikeType) {
        case Obj::Entity::SpikeLeft:
            this->rotateLeft();
            break;
        case Obj::Entity::SpikeRight:
            this->rotateRight();
            break;
        case Obj::Entity::SpikeTop:
            this->rotateTop();
            break;
        default:
            break;
    }
}