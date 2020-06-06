#pragma once

#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Consts.h"
#include <iostream>
#include <memory>


class Camera {
public:
    Camera(Window& window, sf::View view) : camera{view}, window{window} {
        std::cout << "Witam camera constructor\n";
        this->setCameraConstants();
        std::cout << "Zegnam\n";
    }

    void update() {
        auto cameraX = sprite->getPosition().x + halvedSpriteWidth;
        auto cameraY = sprite->getPosition().y + halvedSpriteHeight;
        std::cout << cameraX <<  " " <<cameraY << std::endl;

        if (cameraX > rightBorderBoundary) { std::cout << "X right collision\n"; }
        else if (cameraX < leftBorderBoundary) { std::cout << "X left collision\n";}
        else if (cameraY > bottomBorderBoundary) { std::cout << "Y bottom collision\n";}
        else if (cameraY < topBorderBoundary) { std::cout << "Y top collision\n";}
        else
        camera.setCenter(cameraX, cameraY);

        /** Four possible camera collision conditions */
//    if (cameraX < camera.getSize().x / 2) { std::cout << "X left coll\n"; }
//    if (cameraX > consts::blocksCountWidth * 32 - camera.getSize().x / 2) { std::cout << "X right coll\n";}
//    if (cameraY < camera.getSize().y / 2) { std::cout << " Y top coll \n"; }
//    if (cameraY > consts::blocksCountHeight * 32 - camera.getSize().y / 2) { std::cout << " Y bottom coll\n"; }
//    else
    }

    auto& getCamera() const {
        return camera;
    }

    void setController(sf::Sprite& sprite) {
        this->sprite = &sprite;
        this->setControllerConstants();
    }

private:
    sf::View camera;
    Window& window;
    sf::Sprite* sprite = nullptr;


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

    void setCameraConstants() {
        std::cout << "1\n";
        cameraWidth = camera.getSize().x;
        halvedCameraWidth = cameraWidth / 2.0;
        std::cout << "2\n";

        cameraHeight = camera.getSize().y;
        halvedCameraHeight = cameraHeight / 2.0;

        std::cout << "3\n";
        mapWidth =  consts::blocksCountWidth  * 32;
        mapHeight = consts::blocksCountHeight * 32;

        std::cout << "4\n";
        leftBorderBoundary = halvedCameraWidth;
        rightBorderBoundary = mapWidth - halvedCameraWidth;
        topBorderBoundary = halvedCameraHeight;
        bottomBorderBoundary = mapHeight - halvedCameraHeight;
        std::cout << "5\n";
    }

    void setControllerConstants() {
        halvedSpriteWidth = sprite->getTexture()->getSize().x / 2.0;
        halvedSpriteHeight = sprite->getTexture()->getSize().y / 2.0;
    }

};


