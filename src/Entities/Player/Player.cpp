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
    sprite.move(0, velY * dt + gravity * (dt * dt) * 0.5f);

    if (velY > 1000) {
        velY = 1000;
    } else {
        velY += gravity * dt;
    }
}

void Player::gravityFrame(float dt) {
    sprite.move(0.0f, dt * (gravVelY + dt * gravity * 0.5f));

    if (gravVelY > 1000.0f) {
        gravVelY = 1000.0f;
    } else {
        gravVelY += dt * gravity;
    }
}

void Player::restartJumpTime() {
    gravVelY = 0.0;
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

bool Player::isIntersecting(const Spike& entity) const {
    return this->getGlobalBounds().intersects(entity.getGlobalBounds());
}

bool Player::isIntersecting(const HeartCollectible& entity) const {
    return this->getGlobalBounds().intersects(entity.getGlobalBounds());
}

bool Player::isIntersecting(const Objective& entity) const {
    return this->getGlobalBounds().intersects(entity.getGlobalBounds());
}

void Player::kill(LivesHUD& livesHUD) {
    livesHUD.decreaseLife();
    setToStartingPosition();
    movingState = MovingState::standing;
    jumpingState = JumpingState::onGround;
    this->restartJumpTime();
}

sf::Vector2f Player::getStartingPosition() const {
    return startingPosition;
}

void Player::setToStartingPosition() {
    setPosition(startingPosition);
}

void Player::setStartingPosition() {
    startingPosition = this->sprite.getPosition();
}