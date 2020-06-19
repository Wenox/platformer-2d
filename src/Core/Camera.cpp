/** @file */

#include <Configuration.h>
#include "Camera.h"


Camera::Camera(const sf::View& view) noexcept
    : cameraView{view}
{
    this->setCameraConstants();
}


void Camera::updateX() noexcept {
    /** Detect Left, Right or None collision. Store it in #solvedNow and return correct #solvedX position. */
    float solvedX = detectCollisionX();

    /** Based on #previouslySolvedOtherAxis computed in updateY(), which is either Bot, Top or None - we can respond correctly to the corners and set correct Camera position. */
    std::visit(overload{
            [&](Bot&)   { cameraView.setCenter(solvedX, bottomBorderBoundary); },
            [&](Top&)   { cameraView.setCenter(solvedX, topBorderBoundary); },
            [&](None&)  { cameraView.setCenter(solvedX, controller->getPosition().y + halvedSpriteHeight); },
            [&](auto) noexcept { }
    }, previouslySolvedOtherAxis);

    /** Upon exit, ypdate #previouslySolvedOtherAxis with what we just #solvedNow: either Top, Bot or None. */
    storeJustSolvedForOtherAxis(solvedNow);
}

void Camera::updateY() noexcept {
    /** Detect Top, Bot or None collision. Store it in #solvedNow and return correct #solvedY position. */
    float solvedY = detectCollisionY();

    /** Based on #previouslySolvedOtherAxis computed in updateX(), which is either Left, Right or None - we can respond correctly to the corners and set correct Camera position.*/
    std::visit(overload{
            [&](Left&)  {cameraView.setCenter(leftBorderBoundary, solvedY); },
            [&](Right&) {cameraView.setCenter(rightBorderBoundary, solvedY); },
            [&](auto) noexcept { }
    }, previouslySolvedOtherAxis);

    /** Upon exit, update #previouslySolvedOtherAxis with what we just #solvedNow: either Top, Bot or None. */
    storeJustSolvedForOtherAxis(solvedNow);
}

float Camera::detectCollisionX() noexcept {
    /** Check X position after sprite was moved on X axis. */
    const auto cameraX = controller->getPosition().x + halvedSpriteWidth;

    /** Calculate correct resolved non-colliding X position. */
    float xCoord{};

    if (cameraX > rightBorderBoundary) {
        xCoord = rightBorderBoundary;
        solvedNow = CurrentCollision::Right; ///< There was a Right collision, so store that fact for possible corner-collision response.
    } else if (cameraX < leftBorderBoundary) {
        xCoord = leftBorderBoundary;
        solvedNow = CurrentCollision::Left; ///< There was a Left collision, so store that fact for possible corner-collision response.
    } else {
        xCoord = cameraX;
        solvedNow = CurrentCollision::None; ///< There was None collision. For sure not a corner collision.
    }

    return xCoord;
}

float Camera::detectCollisionY() noexcept {
    /** \example
     * Check Y position after sprite was moved on Y axis. */
    const auto cameraY = controller->getPosition().y + halvedSpriteHeight;

    /** \example Calculate correct resolved non-colliding Y position. */
    float yCoord{};

    if (cameraY > bottomBorderBoundary) {
        yCoord = bottomBorderBoundary;
        solvedNow = CurrentCollision::Bot; ///< There was a Bot collision, so store that fact for possible corner-collision response.
    } else if (cameraY < topBorderBoundary) {
        yCoord = topBorderBoundary;
        solvedNow = CurrentCollision::Top; ///< There was a Top collision, so store that fact for possible corner-collision response.
    } else {
        yCoord = cameraY;
        solvedNow = CurrentCollision::None; ///< There was None collision. For sure not a corner collision.
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

void Camera::storeJustSolvedForOtherAxis(CurrentCollision wasCollision) noexcept {
    switch (wasCollision) {
        case CurrentCollision::Left:
            previouslySolvedOtherAxis = Left{};
            break;
        case CurrentCollision::Right:
            previouslySolvedOtherAxis = Right{};
            break;
        case CurrentCollision::None:
            previouslySolvedOtherAxis = None{};
            break;
        case CurrentCollision::Top:
            previouslySolvedOtherAxis = Top{};
            break;
        case CurrentCollision::Bot:
            previouslySolvedOtherAxis = Bot{};
            break;
    }
}

void Camera::setCameraConstants() noexcept {
    cameraWidth  = cameraView.getSize().x;
    cameraHeight = cameraView.getSize().y;

    halvedCameraWidth  = cameraWidth  / 2.0;
    halvedCameraHeight = cameraHeight / 2.0;

    mapWidth = config::blocksCountWidth * 32;
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
