#include "Configuration.h"
#include "Camera.h"


Camera::Camera(const sf::View& view) noexcept
    : cameraView{view}
{
    this->setCameraConstants();
}

/** Updating one axis at a time simplifies everything.
 *
 *  Upon entering updateX(), we know if in previous frame within updateY()
 *  method there was a Top, Bot or None collision, because we started it in previouslySolvedOnOtherAxis
 *  container.
 *
 *  Similiarly, upon exiting updateX(), we store Left, Right or None inside previouslySolvedOnOtherAxis,
 *  depending on collision type. */
void Camera::updateX() noexcept {
    float solvedX = detectCollisionX();

    std::visit(overload{
            [&](Bot&)   { cameraView.setCenter(solvedX, bottomBorderBoundary); },
            [&](Top&)   { cameraView.setCenter(solvedX, topBorderBoundary); },
            [&](None&)  { cameraView.setCenter(solvedX, controller->getPosition().y + halvedSpriteHeight); },
            [&](auto) noexcept { }
    }, previouslySolvedOnOtherAxis);

    storeJustSolvedForOtherAxis(solvedNow);
}

void Camera::updateY() noexcept {
    float solvedY = detectCollisionY();

    std::visit(overload{
            [&](Left&)  {cameraView.setCenter(leftBorderBoundary,  solvedY); },
            [&](Right&) {cameraView.setCenter(rightBorderBoundary, solvedY); },
            [&](auto) noexcept { }
    }, previouslySolvedOnOtherAxis);

    storeJustSolvedForOtherAxis(solvedNow);
}

float Camera::detectCollisionX() noexcept {
    const auto cameraX = controller->getPosition().x + halvedSpriteWidth;

    float xCoord{};
    if (cameraX > rightBorderBoundary) {
        xCoord = rightBorderBoundary;
        solvedNow = CurrentCollision::Right;
    } else if (cameraX < leftBorderBoundary) {
        xCoord = leftBorderBoundary;
        solvedNow = CurrentCollision::Left;
    } else {
        xCoord = cameraX;
        solvedNow = CurrentCollision::None;
    }

    return xCoord;
}

float Camera::detectCollisionY() noexcept {
    const auto cameraY = controller->getPosition().y + halvedSpriteHeight;

    float yCoord{};

    if (cameraY > bottomBorderBoundary) {
        yCoord = bottomBorderBoundary;
        solvedNow = CurrentCollision::Bot;
    } else if (cameraY < topBorderBoundary) {
        yCoord = topBorderBoundary;
        solvedNow = CurrentCollision::Top;
    } else {
        yCoord = cameraY;
        solvedNow = CurrentCollision::None;
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

void Camera::storeJustSolvedForOtherAxis(CurrentCollision nextCollision) noexcept {
    switch (nextCollision) {
        case CurrentCollision::Left:
            previouslySolvedOnOtherAxis = Left{};
            break;
        case CurrentCollision::Right:
            previouslySolvedOnOtherAxis = Right{};
            break;
        case CurrentCollision::None:
            previouslySolvedOnOtherAxis = None{};
            break;
        case CurrentCollision::Top:
            previouslySolvedOnOtherAxis = Top{};
            break;
        case CurrentCollision::Bot:
            previouslySolvedOnOtherAxis = Bot{};
            break;
    }
}

void Camera::setCameraConstants() noexcept {
    cameraWidth  = cameraView.getSize().x;
    cameraHeight = cameraView.getSize().y;

    halvedCameraWidth  = cameraWidth  / 2.0;
    halvedCameraHeight = cameraHeight / 2.0;

    mapWidth  = config::blocksCountWidth * 32;
    mapHeight = config::blocksCountHeight * 32;

    leftBorderBoundary   = halvedCameraWidth;
    topBorderBoundary    = halvedCameraHeight;
    rightBorderBoundary  = mapWidth  - halvedCameraWidth;
    bottomBorderBoundary = mapHeight - halvedCameraHeight;
}

void Camera::setControllerConstants() noexcept {
    halvedSpriteWidth  = controller->getTexture()->getSize().x / 2.0;
    halvedSpriteHeight = controller->getTexture()->getSize().y / 2.0;
}
