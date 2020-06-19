/** @file */

#include <StateGame.h>
#include <StateMenu.h>
#include <StateMapLoader.h>
#include <StateOptions.h>
#include <StatePaused.h>
#include <StateKeybinds.h>
#include <StateRestart.h>
#include <States/StateAbout.h>
#include "Game.h"


Game::Game()
        : window{"Platformer"}
{
    this->createStates();
}

void Game::createStates() {
    state::menuID     = stateMachine.insert(std::make_shared<StateMenu>     (stateMachine, window, resources));
    state::loaderID   = stateMachine.insert(std::make_shared<StateMapLoader>(stateMachine, window, resources));
    state::optionsID  = stateMachine.insert(std::make_shared<StateOptions>  (stateMachine, window, resources));
    state::keybindsID = stateMachine.insert(std::make_shared<StateKeybinds> (stateMachine, window, resources));
    state::pausedID   = stateMachine.insert(std::make_shared<StatePaused>   (stateMachine, window, resources));
    state::restartID  = stateMachine.insert(std::make_shared<StateRestart>  (stateMachine, window, resources));
    state::aboutID    = stateMachine.insert(std::make_shared<StateAbout>    (stateMachine, resources));

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


Window& Game::getWindow() {
    return window;
}
ResourceManager& Game::getResources() {
    return resources;
}
StateMachine& Game::getStateMachine() {
    return stateMachine;
}