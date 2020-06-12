#include "Player.h"

Player::Player(sf::Vector2f position)
    : Entity{position}
{}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

float Player::getVelocityX() const {
    return velX;
}

float Player::getVelocityY() const {
    return velY;
}

void Player::setVelocityY(float newVal) {
    this->velY = newVal;
}

void Player::jumpFrame(float dt) {
    jumpTime += dt;
    sprite.move(0, velY * jumpTime);

    if (velY < consts::terminalVelocity) {
        velY += consts::gravity * jumpTime;
    }
}

void Player::gravityFrame(float dt) {
    jumpTime += dt;
    sprite.move(0, gravVelY * jumpTime);

    if (gravVelY < consts::terminalVelocity) {
        gravVelY += consts::gravity * jumpTime;
    }
}

void Player::restartJumpTime() {
    jumpTime = 0.0;
}

void Player::landOnGroundUpdate() {
    this->jumpingState = JumpingState::onGround;
    this->setVelocityY(consts::initialJumpVelocity);
    this->restartJumpTime();
}

void Player::hitCeilingUpdate() {
    this->setVelocityY(consts::hitCeilingVelocity);
}

bool Player::isDetectingGround(const std::vector<std::unique_ptr<Entity>>& blocks) const {
    for (std::size_t i = 0; i < blocks.size(); i++) { /** todo: range-based */
        if (blocks[i]->getGlobalBounds().contains(left(),  bot() + detectorRange)
            ||  blocks[i]->getGlobalBounds().contains(right(), bot() + detectorRange)) {
            return true;
        }
    }
    return false;
}

