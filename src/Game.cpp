#include <States/StateGame.h>
#include <States/StateInitializer.h>
#include <States/StateMenu.h>
#include "Game.h"

Game::Game()
    : window{"Platformer"},
      stateMachine{} {

    this->init();
}

void Game::init() {
    auto stateMenuID = stateMachine.insert(std::make_shared<StateMenu>(stateMachine, window));
    auto stateGameID = stateMachine.insert(std::make_shared<StateGame>(stateMachine, window));
    auto stateInitializerID = stateMachine.insert(std::make_shared<StateInitializer>(stateMachine, window));



    std::cout << "stateMenuID: " << stateMenuID << std::endl;
    std::cout << "stateGameID: " << stateGameID << std::endl;
    std::cout << "stateInitializerID: " << stateInitializerID << std::endl;
    stateMachine.switchTo(1);
}

void Game::processInput() {
    stateMachine.processInput();
}

void Game::update() {
    window.update();
    stateMachine.update(dt);
}

void Game::draw() {
    window.beginDraw();
    stateMachine.draw(window);
    window.endDraw();
}

void Game::run() {
    while (this->isRunning()) {
        computeDeltaTime();
        this->processInput();
        this->update();
        this->draw();
    }
}

bool Game::isRunning() const {
    return window.isOpen();
}

void Game::computeDeltaTime() {
    dt = clock.restart().asSeconds();
}
