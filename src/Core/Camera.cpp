#include <Consts.h>
#include "Camera.h"


Camera::Camera(const sf::View& view) noexcept
    : cameraView{view}
{
    this->setCameraConstants();
}


void Camera::updateX() noexcept {
    float xCoord = determineNextCollisionX();

    std::visit(overload{
            [&](Bot&)   { cameraView.setCenter(xCoord, bottomBorderBoundary); },
            [&](Top&)   { cameraView.setCenter(xCoord, topBorderBoundary); },
            [&](None&)  { cameraView.setCenter(xCoord, controller->getPosition().y + halvedSpriteHeight); },
            [&](auto)   { }
    }, collider);

    updateColliderState(nextCollision);
}

void Camera::updateY() noexcept {
    float yCoord = determineNextCollisionY();

    std::visit(overload{
            [&](Left&)  {cameraView.setCenter(leftBorderBoundary,  yCoord); },
            [&](Right&) {cameraView.setCenter(rightBorderBoundary, yCoord); },
            [&](auto)   { }
    }, collider);

    updateColliderState(nextCollision);
}

float Camera::determineNextCollisionX() noexcept {
    const auto cameraX = controller->getPosition().x + halvedSpriteWidth;

    float xCoord{};

    if (cameraX > rightBorderBoundary) {
        xCoord = rightBorderBoundary;
        nextCollision = Collision::Right;
    } else if (cameraX < leftBorderBoundary) {
        xCoord = leftBorderBoundary;
        nextCollision = Collision::Left;
    } else {
        xCoord = cameraX;
        nextCollision = Collision::None;
    }

    return xCoord;
}

float Camera::determineNextCollisionY() noexcept {
    const auto cameraY = controller->getPosition().y + halvedSpriteHeight;

    float yCoord{};

    if (cameraY > bottomBorderBoundary) {
        yCoord = bottomBorderBoundary;
        nextCollision = Collision::Bot;
    } else if (cameraY < topBorderBoundary) {
        yCoord = topBorderBoundary;
        nextCollision = Collision::Top;
    } else {
        yCoord = cameraY;
        nextCollision = Collision::None;
    }

    return yCoord;
}

sf::View& Camera::getCameraView() noexcept {
    return cameraView;
}

void Camera::setController(Entity& controllingEntity) noexcept {
    this->controller = &controllingEntity.getSprite();
    this->setControllerConstants();
}

void Camera::updateColliderState(Collision nextColl) noexcept {
    switch (nextColl) {
        case Collision::Left:
            collider = Left{};
            break;
        case Collision::Right:
            collider = Right{};
            break;
        case Collision::None:
            collider = None{};
            break;
        case Collision::Top:
            collider = Top{};
            break;
        case Collision::Bot:
            collider = Bot{};
            break;
    }
}

void Camera::setCameraConstants() noexcept {
    cameraWidth  = cameraView.getSize().x;
    cameraHeight = cameraView.getSize().y;

    halvedCameraWidth  = cameraWidth  / 2.0;
    halvedCameraHeight = cameraHeight / 2.0;

    mapWidth =  consts::blocksCountWidth  * 32;
    mapHeight = consts::blocksCountHeight * 32;

    leftBorderBoundary   = halvedCameraWidth;
    topBorderBoundary    = halvedCameraHeight;
    rightBorderBoundary  = mapWidth  - halvedCameraWidth;
    bottomBorderBoundary = mapHeight - halvedCameraHeight;
}

void Camera::setControllerConstants() noexcept {
    halvedSpriteWidth  = controller->getTexture()->getSize().x / 2.0;
    halvedSpriteHeight = controller->getTexture()->getSize().y / 2.0;
}
