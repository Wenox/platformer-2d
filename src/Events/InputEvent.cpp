#include "InputEvent.h"


InputEvent::InputEvent(Player& player, ResourceManager& resources)
    : player{player}
    , resources{resources}
{}

void InputEvent::update() {
    updateHorizontal();
    updateVertical();
}

void InputEvent::updateHorizontal() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player.movingState = MovingState::movingRight;
        player.getSprite().setTexture(resources.getTextures().get(res::Texture::PlayerRight));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player.movingState = MovingState::movingLeft;
        player.getSprite().setTexture(resources.getTextures().get(res::Texture::PlayerLeft));
    } else {
        player.movingState = MovingState::standing;
        player.getSprite().setTexture(resources.getTextures().get(res::Texture::Player));
    }
}

void InputEvent::updateVertical() {
    if (player.jumpingState == JumpingState::onGround) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.jumpingState = JumpingState::jumping;
        }
    }
}
