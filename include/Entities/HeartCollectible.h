#pragma once

#include "Entity.h"


class HeartCollectible : public Entity {
private:
    bool collected = false;
public:
    explicit HeartCollectible(sf::Vector2f position);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool wasCollected() const;
    void setCollected(bool status);
};


