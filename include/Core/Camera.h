#pragma once

#include <variant>
#include "Entity.h"
#include "Overload.h"


class Camera {
private:
    struct None{};
    struct Left{};
    struct Right{};
    struct Top{};
    struct Bot{};

    enum class CurrentCollision {
        None,
        Left,
        Right,
        Top,
        Bot
    };

    std::variant<None, Left, Right, Top, Bot> previouslySolvedOnOtherAxis{None{}};
    CurrentCollision solvedNow{CurrentCollision::None};

    sf::View cameraView;

    sf::Sprite* controller{nullptr};

public:
    explicit Camera(const sf::View& view) noexcept;

    void updateX() noexcept;
    void updateY() noexcept;

    void storeJustSolvedForOtherAxis(CurrentCollision wasCollision) noexcept;

    float detectCollisionX() noexcept;
    float detectCollisionY() noexcept;

    sf::View& getCameraView() noexcept;
    void setController(Entity& controllingEntity) noexcept;

private:
    float cameraWidth{};
    float cameraHeight{};
    float halvedCameraWidth{};
    float halvedCameraHeight{};

    float mapWidth{};
    float mapHeight{};

    float leftBorderBoundary{};
    float rightBorderBoundary{};
    float topBorderBoundary{};
    float bottomBorderBoundary{};

    float halvedSpriteWidth{};
    float halvedSpriteHeight{};

    void setCameraConstants() noexcept;
    void setControllerConstants() noexcept;
};