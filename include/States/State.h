#pragma once

#include <SFML/Graphics.hpp>
#include "Window.h"

class State {
public:
    virtual ~State() = default;

    virtual void onCreate() = 0;
    virtual void onDestroy() = 0;

    virtual void onActivate() {};
    virtual void onDeactivate() {};

    virtual void processInput() {};
    virtual void update(float dt) {};
    virtual void draw(Window& window) {};
};