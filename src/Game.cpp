#include "Game.h"

Game::Game()
    : window{"Platformer"} {
    this->init();
}

void Game::processInput() {

}

void Game::update() {
    window.update();
}

void Game::draw() {
    window.beginDraw();
    // window.draw(drawable_obj);
    window.endDraw();
}

void Game::run() {
    while (this->isRunning()) {
        this->processInput();
        this->update();
        this->draw();
    }
}

bool Game::isRunning() const {
    return window.isOpen();
}