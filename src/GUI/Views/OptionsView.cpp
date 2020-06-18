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
    createBackground("../resources/test8.png");

    createPanels();
    createButtons();
    createLabels();
    createCheckBoxes();
    createSoundVolumeSlider();
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

void OptionsView::createButtons() {
    for (auto i{0u}; auto btn : Options::Buttons) {
        const auto& btnName = optionsConfig.widgetsNames[btn];
        widgets.emplace_back(tgui::Button::create(btnName));

        this->loadWidget(widgets[i]);
        ++i;
    }
}

void OptionsView::loadWidget(tgui::Widget::Ptr& widget) {
    config.prepare(widget);
    widget->setPosition({view.getTarget()->getSize().x / 2 - Gui::Config<>::width / 2,
                         Options::Config::offsetY + view.getTarget()->getSize().y / 9 * ++buttonsCounter});
    view.add(widget);
}

void OptionsView::createPanels() {
    createMainPanel();
    createButtonsPanel();
}

void OptionsView::createMainPanel() {
    auto mainPanel = tgui::Panel::create({290, 150});
    mainPanel->setPosition(174, 40);
    mainPanel->getRenderer()->setBackgroundColor(tgui::Color::Black);
    mainPanel->setInheritedOpacity(0.35);
    mainPanel->getRenderer()->setBorders({1, 1, 1, 1});
    mainPanel->getRenderer()->setBorderColor(tgui::Color::White);
    view.add(mainPanel, "mainPanel");
}

void OptionsView::createButtonsPanel() {
    auto buttonsPanel = tgui::Panel::create({270, 135});
    buttonsPanel->setPosition(185,405);
    buttonsPanel->getRenderer()->setBackgroundColor(tgui::Color::Black);
    buttonsPanel->setInheritedOpacity(0.35);
    buttonsPanel->getRenderer()->setBorders({1, 1, 1, 1});
    buttonsPanel->getRenderer()->setBorderColor(tgui::Color::White);
    view.add(buttonsPanel, "buttonsPanel");
}

void OptionsView::createCheckBoxes() {
    createFpsCheckBox();
    createSoundCheckBox();
}

void OptionsView::createFpsCheckBox() {
    auto fpsCheckBox = tgui::CheckBox::create();
    fpsCheckBox->setPosition(184, 50);
    fpsCheckBox->setSize(30, 30);
    fpsCheckBox->setChecked(true);
    view.add(fpsCheckBox, "fpsCheckBox");
}

void OptionsView::createSoundCheckBox() {
    auto soundCheckBox = tgui::CheckBox::create();
    soundCheckBox->setPosition(184, 100);
    soundCheckBox->setSize(30, 30);
    soundCheckBox->setChecked(true);
    view.add(soundCheckBox, "soundCheckBox");
}

void OptionsView::createLabels() {
    createFpsLabel();
    createSoundLabel();
}

void OptionsView::createFpsLabel() {
    auto fpsLabel = tgui::Label::create("Show FPS");
    fpsLabel->setTextSize(32);
    fpsLabel->setPosition(224, 45);
    fpsLabel->setInheritedFont(config.font);
    fpsLabel->getRenderer()->setTextColor(tgui::Color::White);
    view.add(fpsLabel, "fpsLabel");
}

void OptionsView::createSoundLabel() {
    auto soundLabel = tgui::Label::create("Enable sound");
    soundLabel->setTextSize(32);
    soundLabel->setPosition(224, 95);
    soundLabel->setInheritedFont(config.font);
    soundLabel->getRenderer()->setTextColor(tgui::Color::White);
    view.add(soundLabel, "soundLabel");
}

void OptionsView::createSoundVolumeSlider() {
    auto soundVolume = tgui::Slider::create(0.0f, 100.0f);
    soundVolume->setPosition(184, 150);
    soundVolume->setSize(270, 20);
    soundVolume->setValue(audioConfig.volume);
    view.add(soundVolume, "soundVolume");
}
