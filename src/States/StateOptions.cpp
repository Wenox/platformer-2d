#include "StateOptions.h"

StateOptions::StateOptions(StateMachine& stateMachine, Window& window, ResourceHolder<res::Texture, sf::Texture>& textures)
        : stateMachine{stateMachine}
        , window{window}
        , gui{window}
        , cornersTextures{{textures[res::Texture::OptionsLeftTopCorner],
                                  textures[res::Texture::OptionsLeftBotCorner],
                                  textures[res::Texture::OptionsRightBotCorner],
                                  textures[res::Texture::OptionsRightTopCorner]}}
{
    for (int i = 0; i < cornersTextures.size(); ++i) {
        corners.at(i).setTexture(cornersTextures.at(i).get());
    }
    corners.at(0).setPosition(0, 0);
    corners.at(1).setPosition(0, 512);
    corners.at(2).setPosition(576, 512);
    corners.at(3).setPosition(576, 0);
}

void StateOptions::onCreate() {
    gui.widgets[to_underlying(Options::Btn::Keybinds)]->connect("Pressed", [&]() {
        stateMachine = state::keybindsID;
    });

    gui.widgets[to_underlying(Options::Btn::GoBack)]->connect("Pressed", [&]() {
        stateMachine = stateMachine.getCameFrom();
    });

    gui.getGui().get("soundCheckBox")->connect("Clicked", [&]() {
        updateSlider();
    });
}

void StateOptions::updateSlider() {
    const auto& slider = gui.getGui().get("soundVolume");
    if (slider->isEnabled()) {
        slider->setEnabled(false);
        slider->setInheritedOpacity(0.5);
    } else {
        slider->setEnabled(true);
        slider->setInheritedOpacity(1.0);
    }
}

void StateOptions::onDeactivate() {
    saveOptions();
}

void StateOptions::processInput() {
    gui.handleEvent(window.getEvent());

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
        stateMachine = stateMachine.getCameFrom();
    }
}

void StateOptions::draw(Window&) {
    for (auto& corner : corners) {
        this->window.draw(corner);
    }
    gui.draw();
}

void StateOptions::update(float dt) {

}

void StateOptions::saveOptions() {
    mySettings.isSoundEnabled = gui.isSoundChecked();
    mySettings.isFpsEnabled = gui.isFpsChecked();
    mySettings.volume = gui.getVolume();
}