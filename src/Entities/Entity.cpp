/** @file */


#include <Configuration.h>
#include "Entity.h"

Entity::Entity(sf::Vector2f position)
    : position{position}
{
    sprite.setPosition(position);
}

Entity::Entity(ResourceHolder<res::Texture, sf::Texture>& textureHolder, res::Texture textureID, sf::Vector2f position)
    : position{position}
{
    sprite.setTexture(textureHolder.get(textureID));
    sprite.setPosition(position);
}

Entity::Entity(ResourceHolder<res::Texture, sf::Texture>& textureHolder, res::Texture textureID)
    : position{0, 0}
{
    sprite.setTexture(textureHolder.get(textureID));
    sprite.setPosition(position);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Entity::move(const sf::Vector2f& offset) {
    sprite.move(offset);
}

void Entity::move(float offsetX, float offsetY) {
    sprite.move(offsetX, offsetY);
}

void Entity::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}

void Entity::setPosition(int x, int y) {
    sprite.setPosition(x, y);
}

sf::FloatRect Entity::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

sf::Sprite& Entity::getSprite() {
    return sprite;
}


float Entity::width() const {
    return sprite.getGlobalBounds().width;
}

float Entity::height() const {
    return sprite.getGlobalBounds().height;
}

float Entity::left() const {
    return sprite.getGlobalBounds().left;
}

float Entity::right() const {
    return left() + width();
}

float Entity::top() const {
    return sprite.getGlobalBounds().top;
}

float Entity::bot() const {
    return top() + height();
}

void Entity::rotateLeft() {
    sprite.rotate(90.0f);
    sprite.move(config::entityWidth, 0);
}

void Entity::rotateRight() {
    sprite.rotate(-90.0f);
    sprite.move(0, config::entityHeight);
}

void Entity::rotateTop() {
    sprite.rotate(180.0f);
    sprite.move(config::entityWidth, config::entityHeight);
}