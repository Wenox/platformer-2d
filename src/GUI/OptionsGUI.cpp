#include "OptionsGUI.h"


void OptionsGUI::buildGUI() {
    gui.add(tgui::Picture::create("../resources/test8.png"));

    auto myPanel = tgui::Panel::create({290, 150});
    myPanel->setPosition(174,40);
    myPanel->getRenderer()->setBackgroundColor(tgui::Color::Black);
    myPanel->setInheritedOpacity(0.35);
    myPanel->getRenderer()->setBorders({1, 1, 1, 1});
    myPanel->getRenderer()->setBorderColor(tgui::Color::White);
    gui.add(myPanel, "myPanel");

    auto btnsPanel = tgui::Panel::create({270, 135});
    btnsPanel->setPosition(185,405);
    btnsPanel->getRenderer()->setBackgroundColor(tgui::Color::Black);
    btnsPanel->setInheritedOpacity(0.35);
    btnsPanel->getRenderer()->setBorders({1, 1, 1, 1});
    btnsPanel->getRenderer()->setBorderColor(tgui::Color::White);
    gui.add(btnsPanel, "btnsPanel");

    for (auto i{0u}; auto btn : Options::Buttons) {
        const auto& btnName = optionsConfig.widgetsNames[btn];
        widgets.emplace_back(tgui::Button::create(btnName));

        this->loadWidget(widgets[i]);
        ++i;
    }



    auto fpsCheckBox = tgui::CheckBox::create();
    fpsCheckBox->setPosition(184, 50);
    fpsCheckBox->setSize(30, 30);
    fpsCheckBox->setChecked(true);
    gui.add(fpsCheckBox, "fpsCheckBox");

    auto fpsLabel = tgui::Label::create("Show FPS");
    fpsLabel->setTextSize(32);
    fpsLabel->setPosition(224, 45);
    fpsLabel->setInheritedFont(config.font);
    fpsLabel->getRenderer()->setTextColor(tgui::Color::White);
    gui.add(fpsLabel, "fpsLabel");

    auto soundCheckBox = tgui::CheckBox::create();
    soundCheckBox->setPosition(184, 100);
    soundCheckBox->setSize(30, 30);
    soundCheckBox->setChecked(true);
    gui.add(soundCheckBox, "soundCheckBox");

    auto soundLabel = tgui::Label::create("Enable sound");
    soundLabel->setTextSize(32);
    soundLabel->setPosition(224, 95);
    soundLabel->setInheritedFont(config.font);
    soundLabel->getRenderer()->setTextColor(tgui::Color::White);
    gui.add(soundLabel, "soundLabel");



    auto soundVolume = tgui::Slider::create(0.0f, 100.0f);
    soundVolume->setPosition(184, 150);
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
