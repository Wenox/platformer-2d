#include <StateGame.h>
#include <StateMenu.h>
#include <StateMapLoader.h>
#include <StateOptions.h>
#include <StatePaused.h>
#include <StateKeybinds.h>
#include <StateRestart.h>
#include "Game.h"


Game::Game()
    : window{"Platformer"}
{
    this->init();
}

void Game::init() {
    state::menuID    = stateMachine.insert(std::make_shared<StateMenu>(stateMachine, window, resources));
    state::loaderID  = stateMachine.insert(std::make_shared<StateMapLoader>(*this));
    state::optionsID = stateMachine.insert(std::make_shared<StateOptions>(stateMachine, window, resources.getTextures()));
    state::keybindsID = stateMachine.insert(std::make_shared<StateKeybinds>(stateMachine, window));
    state::pausedID  = stateMachine.insert(std::make_shared<StatePaused>(stateMachine, window, resources));
    state::restartID = stateMachine.insert(std::make_shared<StateRestart>(stateMachine, window, resources));

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
