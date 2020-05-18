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

}

void Game::run() {
    while (this->isRunning()) {
        this->processInput();
        this->update();
        this->draw();
    }

    window.update();
    //window.draw();
}

bool Game::isRunning() const {
    return window.isOpen();
}