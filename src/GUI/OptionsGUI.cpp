#include "OptionsGUI.h"


void OptionsGUI::buildGUI() {
    /** todo: try removing bg from PausedState and use it here instead */
//    gui.add(tgui::Picture::create("../resources/background.jpg"));

    auto myPanel = tgui::Panel::create({290, 150});
    myPanel->setPosition(90,40);
    myPanel->getRenderer()->setBackgroundColor(tgui::Color::Black);
    myPanel->setInheritedOpacity(0.35);
    myPanel->getRenderer()->setBorders({1, 1, 1, 1});
    myPanel->getRenderer()->setBorderColor(tgui::Color::White);
    gui.add(myPanel, "myPanel");

    for (auto i{0u}; auto btn : Options::Buttons) {
        const auto& btnName = optionsConfig.widgetsNames[btn];
        widgets.emplace_back(tgui::Button::create(btnName));

        this->loadWidget(widgets[i]);
        ++i;
    }

    auto fpsCheckBox = tgui::CheckBox::create();
    fpsCheckBox->setPosition(100, 50);
    fpsCheckBox->setSize(30, 30);
    fpsCheckBox->setChecked(true);
    gui.add(fpsCheckBox, "fpsCheckBox");

    auto fpsLabel = tgui::Label::create("Show FPS");
    fpsLabel->setTextSize(32);
    fpsLabel->setPosition(140, 45);
    fpsLabel->setInheritedFont({"../resources/CascadiaCode.ttf"});
    fpsLabel->getRenderer()->setTextColor(tgui::Color::White);
    gui.add(fpsLabel, "fpsLabel");

    auto soundCheckBox = tgui::CheckBox::create();
    soundCheckBox->setPosition(100, 100);
    soundCheckBox->setSize(30, 30);
    soundCheckBox->setChecked(true);
    gui.add(soundCheckBox, "soundCheckBox");

    auto soundLabel = tgui::Label::create("Enable sound");
    soundLabel->setTextSize(32);
    soundLabel->setPosition(140, 95);
    soundLabel->setInheritedFont({"../resources/CascadiaCode.ttf"});
    soundLabel->getRenderer()->setTextColor(tgui::Color::White);
    gui.add(soundLabel, "soundLabel");



    auto soundVolume = tgui::Slider::create(0.0f, 100.0f);
    soundVolume->setPosition(100, 150);
    soundVolume->setSize(270, 20);
    soundVolume->setValue(mySettings.volume);
    gui.add(soundVolume, "soundVolume");

}

void OptionsGUI::loadWidget(tgui::Widget::Ptr& widget) {
    config.prepare(widget);
    widget->setPosition({gui.getTarget()->getSize().x / 2 - Gui::Config<>::width / 2,
                         Options::Config::offsetY + gui.getTarget()->getSize().y / 9 * ++btnIndex});
    gui.add(widget);
}