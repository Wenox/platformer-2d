#pragma once

#include <array>
#include "Life.h"
#include "LivesBorder.h"


class LivesHUD : public sf::Drawable {
public:
    explicit LivesHUD(sf::RenderWindow& renderWindow, ResourceHolder<res::Texture, sf::Texture>& textures);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RenderWindow& renderWindow;

    std::array<Life, lives::count> lives;
    LivesBorder border;
    sf::View HUD;

    int availableLives = lives::count;
};





