#include "OptionsGUI.h"


void OptionsGUI::buildGUI() {
    /** todo: try removing bg from PausedState and use it here instead */
//    gui.add(tgui::Picture::create("../resources/background.jpg"));

    for (auto i{0u}; auto btn : Options::Buttons) {
        const auto& btnName = optionsConfig.widgetsNames[btn];
        widgets.emplace_back(tgui::Button::create(btnName));

        this->loadWidget(widgets[i]);
        ++i;
    }


    auto checkBox = tgui::CheckBox::create();
    checkBox->setPosition(100, 200);
    checkBox->setSize(50, 50);
    gui.add(checkBox, "soundCheckBox");


    auto panel = tgui::Panel::create({384, 256});
    panel->setVisible(false);
    panel->setPosition(128, 200);
    panel->getRenderer()->setBackgroundColor(tgui::Color::Red);
    panel->getRenderer()->setOpacity(1.0);
    panel->getRenderer()->setBorderColor(tgui::Color::Black);
    panel->getRenderer()->setBorders({1, 1, 1, 1});

    sf::Texture texture;
    if (!texture.loadFromFile("../resources/registerBg.png")) throw std::runtime_error("cant find registerBg");
    panel->getRenderer()->setTextureBackground(texture);

    auto toolTip = tgui::Label::create("Press ESC to cancel");
    toolTip->setTextSize(12);

    panel->setToolTip(toolTip);


    auto myLabel = tgui::Label::create();
    myLabel->setPosition(70, 100);
    myLabel->setText("PRESS KEY...");
    myLabel->setTextSize(28);
    myLabel->getRenderer()->setTextColor(tgui::Color::White);
    myLabel->setInheritedFont(tgui::Font("../resources/coolFont.ttf"));
    panel->add(myLabel);

    auto cancelRegisterLabel = tgui::Label::create("(ESC to cancel)");
    cancelRegisterLabel->getRenderer()->setTextColor(tgui::Color{191, 191, 191});
    cancelRegisterLabel->setPosition(100, 140);
    cancelRegisterLabel->setTextSize(16);
    cancelRegisterLabel->setInheritedFont(tgui::Font("../resources/coolFont.ttf"));
    panel->add(cancelRegisterLabel);

    gui.add(panel, "panel");
}

void OptionsGUI::loadWidget(tgui::Widget::Ptr& widget) {
    config.prepare(widget);
    widget->setPosition({gui.getTarget()->getSize().x / 2 - Gui::Config<>::width / 2,
                         Options::Config::offsetY + gui.getTarget()->getSize().y / 9 * ++btnIndex});
    gui.add(widget);
}