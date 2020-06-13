#include "GUI/HUD/LivesHUD.h"


LivesHUD::LivesHUD(sf::RenderWindow& renderWindow, ResourceHolder<res::Texture, sf::Texture>& textures)
    : renderWindow{renderWindow}
    , border{renderWindow.getDefaultView().getViewport()}
{
    const auto& viewport = renderWindow.getDefaultView().getViewport();
    for (auto i = 0; auto& life : lives) {
        life.getSprite().setTexture(textures[res::Texture::Heart]);
        life.setPosition(viewport.left + lives::heartOffsetX + lives::boxSide * i,
                         viewport.top  + lives::heartOffsetY);
        ++i;
    }
}

void LivesHUD::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    renderWindow.setView(HUD);

    target.draw(border, states);
    for (const auto& life : lives) {
        target.draw(life, states);
    }
}