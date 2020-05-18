#pragma once


#include "Window.h"

class Game {
public:
    Game();

    void run();
private:
    Window window;

    void init() {}

    void processInput();
    void update();
    void draw();

    bool isRunning() const;
};


