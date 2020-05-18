#pragma once

#include <SFML/Graphics.hpp>

class State {
public:
    virtual void onCreate() = 0;
    virtual void onDestroy() = 0;

    virtual ~State() = default;

    virtual void onActivate() {};
    virtual void onDeactivate() {};

    virtual void processInput() {};
    virtual void update(float dt) {};
    virtual void draw(sf::Window& window) {};
};