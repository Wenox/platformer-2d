#include "Player.h"


Player::Player(sf::Vector2f position)
    : Entity{position}
{}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Player::jumpFrame(float dt) {
    sprite.move(0, jumpVelocity * dt + gravity * (dt * dt) * 0.5f);
    updateVelocity(jumpVelocity, dt);
}

void Player::gravityFrame(float dt) {
    sprite.move(0.0f, dt * (gravVelocity + dt * gravity * 0.5f));
    updateVelocity(gravVelocity, dt);
}

void Player::updateVelocity(float& velocity, float dt) const noexcept {
    if (velocity > config::terminalVelocity) {
        velocity = config::terminalVelocity;
    } else {
        velocity += gravity * dt;
    }
}

void Player::resetGravVelocity() {
    gravVelocity = 0.0;
}

void Player::landOnGroundUpdate() {
    this->jumpingState = JumpingState::onGround;
    this->setJumpVelocity(config::initialJumpVelocity);
    this->resetGravVelocity();
}

void Player::hitCeilingUpdate() {
    this->setJumpVelocity(config::hitCeilingVelocity);
}

bool Player::isDetectingGround(const std::vector<std::unique_ptr<Entity>>& blocks) const {
    for (const auto & block : blocks) {
        if (block->getGlobalBounds().contains(left(),  bot() + feetDetectorRange)
        ||  block->getGlobalBounds().contains(right(), bot() + feetDetectorRange)) {
            return true;
        }
    }
    return false;
}

bool Player::isIntersecting(const Entity& entity) const {
    return this->getGlobalBounds().intersects(entity.getGlobalBounds());
}

void Player::kill(LivesOverlay& lives) {
    lives.decreaseLife();
    setToStartingPosition();
    movingState = MovingState::standing;
    this->landOnGroundUpdate();
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

float Player::getVelocityX() const {
    return velocityX;
}

[[maybe_unused]] float Player::getJumpVelocity() const {
    return jumpVelocity;
}

[[maybe_unused]] float Player::getGravVelocity() const {
    return gravVelocity;
}

void Player::setJumpVelocity(float newVal) {
    this->jumpVelocity = newVal;
}