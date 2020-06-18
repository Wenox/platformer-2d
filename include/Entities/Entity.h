#pragma once

#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "ResourceHolder.h"


class Entity : public sf::Drawable, public sf::Transformable {
public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void move(const sf::Vector2f& offset);
    void move(float offsetX, float offsetY);

    void setPosition(const sf::Vector2f& position);
    void setPosition(int x, int y);

    sf::FloatRect getGlobalBounds() const;
    sf::Sprite& getSprite();

    float x() const;
    float y() const;

    float width() const;
    float height() const;
    float left() const;
    float right() const;
    float top() const;
    float bot() const;

    void rotateLeft();
    void rotateRight();
    void rotateTop();

    virtual ~Entity() = default;
    Entity(Entity const&) = default;
    Entity(Entity&&) noexcept = default;
    Entity& operator=(Entity const&) = default;
    Entity& operator=(Entity&&) noexcept = default;


protected:
    explicit Entity(sf::Vector2f position);
    Entity(ResourceHolder<res::Texture, sf::Texture>& textureHolder, res::Texture textureID, sf::Vector2f position);
    Entity(ResourceHolder<res::Texture, sf::Texture>& textureHolder, res::Texture textureID);

    sf::Sprite   sprite;
    sf::Vector2f position; /** todo: do I need it? */
};


