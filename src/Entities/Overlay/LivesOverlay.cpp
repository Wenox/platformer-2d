#include "Entities/Overlay/LivesOverlay.h"


LivesOverlay::LivesOverlay(sf::RenderWindow& renderWindow, ResourceHolder<res::Texture, sf::Texture>& textures)
    : renderWindow{renderWindow}
    , border{renderWindow.getDefaultView().getViewport()}
{
    const auto& viewport = renderWindow.getDefaultView().getViewport();
    for (auto i = 0; auto& life : lives) {
        life.storeAliveTexture(textures[res::Texture::Heart]);
        life.storeDeadTexture(textures[res::Texture::HeartEmpty]);
        life.getSprite().setTexture(life.getAliveTexture());
        life.setPosition(viewport.left + lives::heartOffsetX + lives::boxSide * i,
                         viewport.top  + lives::heartOffsetY);
        ++i;
    }
}

void LivesOverlay::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    renderWindow.setView(HUD);

    target.draw(border, states);
    for (const auto& life : lives) {
        target.draw(life, states);
    }
}