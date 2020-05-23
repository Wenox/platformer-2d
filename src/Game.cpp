#include <States/StateGame.h>
#include <States/StateInit.h>
#include <States/StateMenu.h>
#include "Game.h"

Game::Game()
    : window{"Platformer"},
      stateMachine{} {

    this->init();

    //this->testResources();
}

void Game::init() {
    state::initID = stateMachine.insert(std::make_shared<StateInit>(stateMachine, window));
    state::menuID = stateMachine.insert(std::make_shared<StateMenu>(stateMachine, window));
    state::gameID = stateMachine.insert(std::make_shared<StateGame>(stateMachine, rm));

    stateMachine += std::make_shared<StateGame>(stateMachine, rm);
    stateMachine += std::make_shared<StateMenu>(stateMachine, window);
    stateMachine += std::make_shared<StateInit>(stateMachine, window);


    std::cout << "stateInitializerID: " << state::initID << std::endl;
    std::cout << "stateMenuID: " << state::menuID << std::endl;
    std::cout << "stateGameID: " << state::gameID << std::endl;
    stateMachine.switchTo(state::gameID);
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
