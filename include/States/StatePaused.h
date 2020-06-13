#pragma once

#include "Resources.h"
#include "StateMachine.h"
#include "ResourceHolder.h"
#include "StateID.h"


class StatePaused : public State {
public:
    StatePaused(StateMachine& stateMachine, Window& window, ResourceHolder<res::Texture, sf::Texture>& textures)
    : stateMachine{stateMachine}
    , window{window}
    , pausedView{{320, 288}, {604, 576}}
    {
        background.setTexture(textures[res::Texture::BgPaused]);
    }

    void onCreate() override {

    }

    void onDestroy() override {

    }

    void onActivate() override {
        window.getWindow().setView(pausedView);
    }

    void processInput() override {

    }
    void update(float dt) override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket)) {
            stateMachine = state::gameID;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            stateMachine = state::menuID;
        }
    }
    void draw(Window& window) override {
        this->window.draw(background);
    }

private:
    StateMachine& stateMachine;
    Window& window;

    sf::Sprite background;
    sf::View pausedView;
};


