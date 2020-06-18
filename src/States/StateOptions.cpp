#include "StateOptions.h"
#include "StateID.h"


StateOptions::StateOptions(StateMachine& stateMachine, Window& window, ResourceManager& resources)
        : stateMachine{stateMachine}
        , window{window}
        , gui{window}
        , cornersTextures{{resources.getTextures()[res::Texture::OptionsLeftTopCorner],
                           resources.getTextures()[res::Texture::OptionsLeftBotCorner],
                           resources.getTextures()[res::Texture::OptionsRightBotCorner],
                           resources.getTextures()[res::Texture::OptionsRightTopCorner]}}
{
    onHoverBtnSound.setBuffer(resources.getSounds()[res::Sound::Bing]);

    for (std::size_t i{0u}; i < cornersTextures.size(); ++i) {
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
        stateMachine.switchToPreviousState();
    });

    gui.getGui().get("fpsCheckBox")->connect("Changed", [&]() {
        audioConfig.isFpsEnabled = gui.isFpsChecked();
    });

    gui.getGui().get("soundCheckBox")->connect("Changed", [&]() {
        saveOptions();
        updateHoverSoundVolume();
        updateSlider();
    });

    gui.getGui().get("soundVolume")->connect("ValueChanged", [&]() {
        audioConfig.volume = gui.getVolume();
        updateHoverSoundVolume();
    });

    for (auto& widget : gui.widgets) {
        widget->connect("MouseEntered", [&]() {
            onHoverBtnSound.play();
        });
    }
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

void StateOptions::onActivate() {
}

void StateOptions::processInput() {
    gui.handleEvent(window.getEvent());

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
        stateMachine.switchToPreviousState();
    }
}

void StateOptions::update(float dt) {

}

void StateOptions::draw(Window&) {
    for (auto& corner : corners) {
        this->window.draw(corner);
    }
    gui.draw();
}

void StateOptions::saveOptions() {
    audioConfig.isSoundEnabled = gui.isSoundChecked();
    audioConfig.isFpsEnabled = gui.isFpsChecked();
    audioConfig.volume = gui.getVolume();
}

void StateOptions::updateHoverSoundVolume() {
    if (audioConfig.isSoundEnabled) {
        onHoverBtnSound.setVolume(audioConfig.volume);
    } else {
        onHoverBtnSound.setVolume(0.0f);
    }
}