#include <States/StateGame.h>
#include <States/StateInit.h>
#include <States/StateMenu.h>
#include <States/StateMapLoader.h>
#include <States/StateOptions.h>
#include <States/StatePaused.h>
#include "Game.h"


Game::Game()
    : window{"Platformer"}
{
    this->init();
}

void Game::init() {
    state::initID = stateMachine.insert(std::make_shared<StateInit>(stateMachine, window));
    state::menuID = stateMachine.insert(std::make_shared<StateMenu>(stateMachine, window, resources, settings));
    state::loaderID = stateMachine.insert(std::make_shared<StateMapLoader>(*this));
    state::optionsID = stateMachine.insert(std::make_shared<StateOptions>(stateMachine, window, settings));
    state::pausedID = stateMachine.insert(std::make_shared<StatePaused>(stateMachine, window, resources.getTextures()));

    stateMachine.switchTo(state::menuID);
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
