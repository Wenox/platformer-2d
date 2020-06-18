#pragma once

#include <SFML/Graphics.hpp> ///< Pass-through
#include "Window.h"


class State {
public:
    virtual ~State() = default;

    virtual void onCreate() {};
    virtual void onDestroy() {};

    virtual void onActivate() {};
    virtual void onDeactivate() {};

    virtual void processInput() = 0;
    virtual void update(float) {};
    virtual void draw(Window&) = 0;
};