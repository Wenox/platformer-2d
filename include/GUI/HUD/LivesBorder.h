#pragma once

#include <SFML/Graphics.hpp>
#include "LivesHUDConfig.h"


class LivesBorder : public sf::Drawable {
public:
    explicit LivesBorder(const sf::Rect<float>& viewport);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RectangleShape border;
    const sf::Rect<float>& viewport;

    void setBorder();
};


