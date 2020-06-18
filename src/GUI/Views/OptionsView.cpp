#include "OptionsView.h"
#include "Settings.h"


OptionsView::OptionsView(Window& window)
    : View{window}
{
    this->init();
}

void OptionsView::init() {
    this->buildGUI();
}


void OptionsView::buildGUI() {
    view.add(tgui::Picture::create("../resources/test8.png"));

    auto myPanel = tgui::Panel::create({290, 150});
    myPanel->setPosition(174,40);
    myPanel->getRenderer()->setBackgroundColor(tgui::Color::Black);
    myPanel->setInheritedOpacity(0.35);
    myPanel->getRenderer()->setBorders({1, 1, 1, 1});
    myPanel->getRenderer()->setBorderColor(tgui::Color::White);
    view.add(myPanel, "myPanel");

    auto btnsPanel = tgui::Panel::create({270, 135});
    btnsPanel->setPosition(185,405);
    btnsPanel->getRenderer()->setBackgroundColor(tgui::Color::Black);
    btnsPanel->setInheritedOpacity(0.35);
    btnsPanel->getRenderer()->setBorders({1, 1, 1, 1});
    btnsPanel->getRenderer()->setBorderColor(tgui::Color::White);
    view.add(btnsPanel, "btnsPanel");

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
    view.add(fpsCheckBox, "fpsCheckBox");

    auto fpsLabel = tgui::Label::create("Show FPS");
    fpsLabel->setTextSize(32);
    fpsLabel->setPosition(224, 45);
    fpsLabel->setInheritedFont(config.font);
    fpsLabel->getRenderer()->setTextColor(tgui::Color::White);
    view.add(fpsLabel, "fpsLabel");

    auto soundCheckBox = tgui::CheckBox::create();
    soundCheckBox->setPosition(184, 100);
    soundCheckBox->setSize(30, 30);
    soundCheckBox->setChecked(true);
    view.add(soundCheckBox, "soundCheckBox");

    auto soundLabel = tgui::Label::create("Enable sound");
    soundLabel->setTextSize(32);
    soundLabel->setPosition(224, 95);
    soundLabel->setInheritedFont(config.font);
    soundLabel->getRenderer()->setTextColor(tgui::Color::White);
    view.add(soundLabel, "soundLabel");



    auto soundVolume = tgui::Slider::create(0.0f, 100.0f);
    soundVolume->setPosition(184, 150);
    soundVolume->setSize(270, 20);
    soundVolume->setValue(audioConfig.volume);
    view.add(soundVolume, "soundVolume");

}

void OptionsView::loadWidget(tgui::Widget::Ptr& widget) {
    config.prepare(widget);
    widget->setPosition({view.getTarget()->getSize().x / 2 - Gui::Config<>::width / 2,
                         Options::Config::offsetY + view.getTarget()->getSize().y / 9 * ++buttonsCounter});
    view.add(widget);
}



bool OptionsView::isSoundChecked() const {
    return this->view.getContainer()->get<tgui::CheckBox>("soundCheckBox")->isChecked();
}

bool OptionsView::isFpsChecked() const {
    return this->view.getContainer()->get<tgui::CheckBox>("fpsCheckBox")->isChecked();
}

float OptionsView::getVolume() const  {
    return this->view.getContainer()->get<tgui::Slider>("soundVolume")->getValue();
}
