#include "StateKeybinds.h"
#include "StateID.h"
#include "Settings.h"


StateKeybinds::StateKeybinds(StateMachine& stateMachine, Window& window, ResourceManager& resourceManager)
        : action{Action::NONE}
        , stateMachine{stateMachine}
        , window{window}
        , gui{window}
{
    onHoverBtnSound.setBuffer(resourceManager.getSounds()[res::Sound::Bing]);
}

void StateKeybinds::onCreate() {
    gui.widgets[to_underlying(Keybinds::Btn::Jump)]->connect("Pressed", [&]() {
        action = Action::Jump;
        gui.getView().get("gamepad")->hideWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
        gui.getView().get("panel")->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(150));
    });
    gui.widgets[to_underlying(Keybinds::Btn::RunLeft)]->connect("Pressed", [&]() {
        action = Action::GoLeft;
        gui.getView().get("gamepad")->hideWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
        gui.getView().get("panel")->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(150));
    });
    gui.widgets[to_underlying(Keybinds::Btn::RunRight)]->connect("Pressed", [&]() {
        action = Action::GoRight;
        gui.getView().get("gamepad")->hideWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
        gui.getView().get("panel")->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(150));
    });

    gui.widgets[to_underlying(Keybinds::Btn::GoBack)]->connect("Pressed", [&]() {
        stateMachine = state::optionsID;
    });

    for (auto& widget : gui.widgets) {
        widget->connect("MouseEntered", [&]() {
            onHoverBtnSound.play();
        });
    }
}

void StateKeybinds::onActivate() {
    updateHoverSoundVolume();
}

void StateKeybinds::processInput() {
    gui.handleEvent(window.getEvent());

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        stateMachine = state::optionsID;
    }
}

void StateKeybinds::update(float dt) {
    if (window.getEvent().front().type == sf::Event::KeyPressed
        and action != Action::NONE) {

        gui.getView().get("panel")->hideWithEffect(tgui::ShowAnimationType::SlideToRight, sf::milliseconds(150));
        gui.getView().get("gamepad")->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));

        if (window.getEvent().front().key.code == sf::Keyboard::Escape) {
            action = Action::NONE;
            return;
        }

        switch (action) {
            case Action::Jump:
                actionMap.set("Jump", window.getEvent().front().key.code);
                break;
            case Action::GoLeft:
                actionMap.set("GoLeft", window.getEvent().front().key.code);
                break;
            case Action::GoRight:
                actionMap.set("GoRight", window.getEvent().front().key.code);
                break;
            default:
                break;
        }

        action = Action::NONE;
    }
}

void StateKeybinds::draw(Window&) {
    gui.draw();
}

void StateKeybinds::updateHoverSoundVolume() {
    if (audioConfig.isSoundEnabled) {
        onHoverBtnSound.setVolume(audioConfig.volume);
    } else {
        onHoverBtnSound.setVolume(0.0f);
    }
}


