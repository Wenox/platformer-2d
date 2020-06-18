#include "StateAbout.h"


StateAbout::StateAbout(StateMachine& stateMachine, ResourceManager& resources)
        : stateMachine{stateMachine}
        , aboutInfo{resources.getTextures()[res::Texture::BgAbout]}
{}

void StateAbout::onCreate() {}

void StateAbout::processInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        stateMachine.switchTo(state::menuID);
    }
}

void StateAbout::update(float) {}

void StateAbout::draw(Window& window) {
    window.draw(aboutInfo);
}