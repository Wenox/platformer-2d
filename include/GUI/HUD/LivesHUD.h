#pragma once

#include <array>
#include "Life.h"
#include "LivesBorder.h"


class LivesHUD : public sf::Drawable {
public:
    explicit LivesHUD(sf::RenderWindow& renderWindow, ResourceHolder<res::Texture, sf::Texture>& textures);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void decreaseLife() {
        availableLives -= 1;
        lives[availableLives].kill();
    }

    void increaseLife() {
        lives[availableLives].revive();
        availableLives += 1;
    }

    bool hasAllLives() const {
        return availableLives >= lives::count;
    }

    bool isDead() const {
        return availableLives <= 0;
    }

    int getAvailableLives() const { return availableLives; }
    bool livesAvailable() const { return availableLives > 0; }

private:
    sf::RenderWindow& renderWindow;

    std::array<Life, lives::count> lives;
    LivesBorder border;
    sf::View HUD;

    int availableLives = lives::count;
};





