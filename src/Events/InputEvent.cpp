#include "InputEvent.h"


InputEvent::InputEvent(Player& player, ResourceManager& resources, Window& window)
    : player{player}
    , resources{resources}
    , window{window}
{
    keys["GoLeft"]  = sf::Keyboard::A;
    keys["GoRight"] = sf::Keyboard::D;
    keys["Jump"]    = sf::Keyboard::W;
}

void InputEvent::update() {
    updateHorizontal();
    updateVertical();
}

void InputEvent::updateHorizontal() {

    if (isPressed(actions->getActionMap()["GoRight"])) {
        player.movingState = MovingState::movingRight;
        player.getSprite().setTexture(resources.getTextures().get(res::Texture::PlayerRight));
    }
    else if (isPressed(actions->getActionMap()["GoLeft"])) {
        player.movingState = MovingState::movingLeft;
        player.getSprite().setTexture(resources.getTextures().get(res::Texture::PlayerLeft));
    }
    else {
        player.movingState = MovingState::standing;
        player.getSprite().setTexture(resources.getTextures().get(res::Texture::Player));
    }
}

bool InputEvent::isPressed(sf::Keyboard::Key myKeyCode) {
    return sf::Keyboard::isKeyPressed(myKeyCode);
}

void InputEvent::updateVertical() {
    if (player.jumpingState == JumpingState::onGround) {
        if (isPressed(actions->getActionMap()["Jump"])) {
            player.jumpingState = JumpingState::jumping;
        }
    }
}
