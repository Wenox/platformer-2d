#include "KeybindsView.h"


KeybindsView::KeybindsView(Window &window)
    : View{window}
{
    this->init();
}

void KeybindsView::init() {
    this->buildGUI();
}

void KeybindsView::buildGUI() {
    view.add(tgui::Picture::create("../resources/bindingsBg.png"));


    auto panelPrompt = tgui::Panel::create({config.width + 72, 48});
    panelPrompt->setPosition(159,8);
    panelPrompt->getRenderer()->setBackgroundColor(tgui::Color::White);
    panelPrompt->setInheritedOpacity(0.35);
    panelPrompt->getRenderer()->setBorders({1, 1, 1, 1});
    panelPrompt->getRenderer()->setBorderColor(tgui::Color::Black);
    view.add(panelPrompt, "panelPrompt");

    auto promptRebindLabel = tgui::Label::create("Rebind your keys");
    promptRebindLabel->setPosition(166, 10);
    promptRebindLabel->setInheritedFont(config.font);
    promptRebindLabel->setTextSize(32);
    promptRebindLabel->getRenderer()->setTextColor(tgui::Color::Black);
    view.add(promptRebindLabel, "promptRebindLabel");


    auto panelButtons = tgui::Panel::create({config.width + 72, 238});
    panelButtons->setPosition(159,335);
    panelButtons->getRenderer()->setBackgroundColor(tgui::Color::Black);
    panelButtons->setInheritedOpacity(0.25);
    panelButtons->getRenderer()->setBorders({1, 1, 1, 1});
    panelButtons->getRenderer()->setBorderColor(tgui::Color::White);
    view.add(panelButtons, "panelButtons");


    auto gamepad = tgui::Picture::create(tgui::Texture{"../resources/gamepad6.png"});
    gamepad->setPosition(170, 75);
    gamepad->setInheritedOpacity(0.6);
    view.add(gamepad, "gamepad");

    auto jumpIcon = tgui::Picture::create(tgui::Texture{"../resources/long-jump2.png"});
    jumpIcon->setPosition(158, 342);
    jumpIcon->setInheritedOpacity(0.3);
    view.add(jumpIcon, "jumpIcon");

    auto leftIcon = tgui::Picture::create(tgui::Texture{"../resources/left-arrow2.png"});
    leftIcon->setPosition(158, 398);
    leftIcon->setInheritedOpacity(0.3);
    view.add(leftIcon, "leftIcon");


    auto rightIcon = tgui::Picture::create(tgui::Texture{"../resources/right-arrow2.png"});
    rightIcon->setInheritedOpacity(0.3);
    rightIcon->setPosition(158, 456);
    view.add(rightIcon, "leftIcon");

    for (auto i{0u}; auto btn : OptionsKeys::Buttons) {
        const auto& btnName = optionsConfig.widgetsNames[btn];
        widgets.emplace_back(tgui::Button::create(btnName));

        this->loadWidget(widgets[i]);
        ++i;
    }

    auto panel = tgui::Panel::create({384, 256});
    panel->setVisible(false);
    panel->setPosition(128, 68);
    panel->getRenderer()->setBackgroundColor(tgui::Color::Red);
    panel->getRenderer()->setOpacity(1.0);
    panel->getRenderer()->setBorderColor(tgui::Color::Black);
    panel->getRenderer()->setBorders({1, 1, 1, 1});

    sf::Texture texture;
    if (!texture.loadFromFile("../resources/registerBg.png")) throw std::runtime_error("cant find registerBg");
    panel->getRenderer()->setTextureBackground(texture);


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

    view.add(panel, "panel");

    auto leftSide = tgui::Picture::create(tgui::Texture{"../resources/side.png"});
    view.add(leftSide, "leftSide");
    auto rightSide = tgui::Picture::create(tgui::Texture{"../resources/side.png"});
    rightSide->setPosition(608, 0);
    view.add(rightSide, "rightSide");
}

void KeybindsView::loadWidget(tgui::Widget::Ptr &widget) {
    config.prepare(widget);
    widget->setPosition({view.getTarget()->getSize().x / 2 - Gui::Config<>::width / 2 + 25,
                         OptionsKeys::Config::offsetY + view.getTarget()->getSize().y / 10 * ++buttonsCounter});
    view.add(widget);
}