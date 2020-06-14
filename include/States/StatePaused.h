#pragma once

#include <SFML/Audio/Sound.hpp>
#include <GUI/PausedGUI.h>
#include <ResourceManager/ResourceManager.h>
#include "Resources.h"
#include "StateMachine.h"
#include "StateID.h"


class StatePaused : public State {
public:
    StatePaused(StateMachine& stateMachine, Window& window, ResourceManager& resources)
    : stateMachine{stateMachine}
    , window{window}
    , pausedView{{320, 288}, {604, 576}}
    , gui{window}
    {
        background.setTexture(resources.getTextures()[res::Texture::BgPaused]);
        onHoverBtnSound.setBuffer(resources.getSounds()[res::Sound::Bing]);
    }

    void onCreate() override {
        gui.widgets[to_underlying(Paused::Btn::resume)]->connect("pressed", [&]() {
            stateMachine = state::gameID;
        });

        gui.widgets[to_underlying(Paused::Btn::options)]->connect("pressed", [&]() {
            stateMachine = state::optionsID;
        });

        gui.widgets[to_underlying(Paused::Btn::menu)]->connect("pressed", [&]() {
            stateMachine = state::menuID;
        });

        for (auto& widget : gui.widgets) {
            widget->connect("MouseEntered", [&]() {
                onHoverBtnSound.play();
            });
        }
    }

    void onDestroy() override {

    }

    void onActivate() override {
        window.getWindow().setView(pausedView);
    }

    void processInput() override {
        gui.handleEvent(window.getEvent());
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
        gui.draw();
    }

private:
    StateMachine& stateMachine;
    Window& window;

    sf::Sprite background;
    sf::View pausedView;

    PausedGUI gui;

    sf::Sound onHoverBtnSound;
};


