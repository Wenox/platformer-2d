/** @file */

#include "Configuration.h"
#include "KeybindsView.h"
#include <iostream>


KeybindsView::KeybindsView(Window &window)
    : View{window}
{
    this->init();
}

void KeybindsView::init() {
    this->buildGUI();
}

void KeybindsView::buildGUI() {
    createBackgroundFrom(config::bg::keybinds);
    createPanels();
    createButtons();
    createIcons();
    createTitleLabel();
    createBorders();

}

void KeybindsView::createPanels() {
    createTitlePanel();
    createButtonsPanel();

    createRebindingPanelGroup();
}

void KeybindsView::createTitlePanel() {
    auto panelTitle = tgui::Panel::create({config.width + 72, 48});

    panelTitle->setPosition(159, 8);
    panelTitle->getRenderer()->setBackgroundColor(tgui::Color::White);
    panelTitle->setInheritedOpacity(0.35);
    panelTitle->getRenderer()->setBorders({1, 1, 1, 1});
    panelTitle->getRenderer()->setBorderColor(tgui::Color::Black);

    view.add(panelTitle, "panelTitle");
}

void KeybindsView::createButtonsPanel() {
    auto panelButtons = tgui::Panel::create({config.width + 72, 238});

    panelButtons->setPosition(159,335);
    panelButtons->getRenderer()->setBackgroundColor(tgui::Color::Black);
    panelButtons->setInheritedOpacity(0.25);
    panelButtons->getRenderer()->setBorders({1, 1, 1, 1});
    panelButtons->getRenderer()->setBorderColor(tgui::Color::White);

    view.add(panelButtons, "panelButtons");
}

void KeybindsView::createRebindingPanelGroup() {
    const auto& parent = createRebindingPanel();
    try {
        addBackgroundInto(parent);
    } catch (const std::exception& e) {
        std::cerr << "Add keybinds background failed, using empty background instead." << std::endl;
        std::cerr << e.what() << std::endl;
    }

    try {
        addPressKeyLabelInto(parent);
        addCancelLabelInto(parent);
    } catch (const std::exception& e) {
        std::cerr << "Add keybinds register labels failed. No such font: " << config::keybindsFontName << std::endl;
        std::cerr << e.what() << std::endl;
    }
}

tgui::Panel::Ptr KeybindsView::createRebindingPanel() {
    auto panel = tgui::Panel::create({384, 256});

    panel->setVisible(false);
    panel->setPosition(128, 68);
    panel->getRenderer()->setBackgroundColor(tgui::Color::Red);
    panel->getRenderer()->setOpacity(1.0);
    panel->getRenderer()->setBorderColor(tgui::Color::Black);
    panel->getRenderer()->setBorders({1, 1, 1, 1});
    view.add(panel, "panel");

    return panel;
}

void KeybindsView::addBackgroundInto(const tgui::Panel::Ptr& parent) {
    sf::Texture texture;
    if (!texture.loadFromFile(config::rebindingBg.data())) {
        throw std::runtime_error("No such resource: " + std::string(config::rebindingBg.data()));
    }
    parent->getRenderer()->setTextureBackground(texture);
}

void KeybindsView::addPressKeyLabelInto(const tgui::Panel::Ptr& parent) {
    auto myLabel = tgui::Label::create();

    myLabel->setPosition(70, 100);
    myLabel->setText("PRESS KEY...");
    myLabel->setTextSize(28);
    myLabel->getRenderer()->setTextColor(tgui::Color::White);
    myLabel->setInheritedFont(tgui::Font(config::keybindsFontName.data()));

    parent->add(myLabel);
}

void KeybindsView::addCancelLabelInto(const tgui::Panel::Ptr& parent) {
    auto cancelRegisterLabel = tgui::Label::create("(ESC to cancel)");

    cancelRegisterLabel->getRenderer()->setTextColor(tgui::Color{191, 191, 191});
    cancelRegisterLabel->setPosition(100, 140);
    cancelRegisterLabel->setTextSize(16);
    cancelRegisterLabel->setInheritedFont(tgui::Font(config::keybindsFontName.data()));

    parent->add(cancelRegisterLabel);
}

void KeybindsView::createButtons() {
    for (auto i{0u}; auto btn : Keybinds::Buttons) {
        const auto& btnName = optionsConfig.widgetsNames[btn];
        widgets.emplace_back(tgui::Button::create(btnName));

        this->loadWidget(widgets[i]);
        ++i;
    }
}

void KeybindsView::loadWidget(tgui::Widget::Ptr &widget) {
    config.prepare(widget);
    widget->setPosition({view.getTarget()->getSize().x / 2 - Gui::Config<>::width / 2 + 25,
                         Keybinds::Config::offsetY + view.getTarget()->getSize().y / 10 * ++buttonsCounter});
    view.add(widget);
}

void KeybindsView::createIcons() {
    try {
        createLargeBgIcon();
        createJumpIcon();
        createRunLeftIcon();
        createRunRightIcon();
    }
    catch (const std::exception& e) {
        std::cout << "Could not load an icon for Keybinds menu" << std::endl;
        std::cerr << e.what() << std::endl;
    }
}


void KeybindsView::createLargeBgIcon() {
    auto largeBgIcon = tgui::Picture::create(tgui::Texture{config::largeBgIcon.data()});

    largeBgIcon->setPosition(170, 75);
    largeBgIcon->setInheritedOpacity(0.6);

    view.add(largeBgIcon, "largeBgIcon");
}

void KeybindsView::createJumpIcon() {
    auto jumpIcon = tgui::Picture::create(tgui::Texture{config::jumpIcon.data()});

    jumpIcon->setPosition(158, 342);
    jumpIcon->setInheritedOpacity(0.3);

    view.add(jumpIcon);
}

void KeybindsView::createRunLeftIcon() {
    auto leftIcon = tgui::Picture::create(tgui::Texture{config::runLeftIcon.data()});

    leftIcon->setPosition(158, 398);
    leftIcon->setInheritedOpacity(0.3);

    view.add(leftIcon);

}

void KeybindsView::createRunRightIcon() {
    auto rightIcon = tgui::Picture::create(tgui::Texture{config::runRightIcon.data()});

    rightIcon->setInheritedOpacity(0.3);
    rightIcon->setPosition(158, 456);

    view.add(rightIcon);
}

void KeybindsView::createTitleLabel() {
    auto promptRebindLabel = tgui::Label::create("Rebind your keys");

    promptRebindLabel->setPosition(166, 10);
    promptRebindLabel->setInheritedFont(Gui::Config<>::font);
    promptRebindLabel->setTextSize(32);
    promptRebindLabel->getRenderer()->setTextColor(tgui::Color::Black);

    view.add(promptRebindLabel, "promptRebindLabel");
}

void KeybindsView::createBorders() {
    try {
        createLeftBorder();
        createRightBorder();
    }
    catch (const std::exception& e) {
        std::cerr << "No such border texture: " << config::sideBorder.data() << std::endl;
        std::cerr << e.what() << std::endl;
    }
}

void KeybindsView::createLeftBorder() {
    auto leftSideBorder = tgui::Picture::create(tgui::Texture{config::sideBorder.data()});
    view.add(leftSideBorder, "leftSideBorder");
}

void KeybindsView::createRightBorder() {
    auto rightSideBorder = tgui::Picture::create(tgui::Texture{config::sideBorder.data()});
    rightSideBorder->setPosition(608, 0);
    view.add(rightSideBorder, "rightSideBorder");
}
