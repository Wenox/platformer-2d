/** @file */

#include <Core/Configuration.h>
#include "MapLoaderView.h"


MapLoaderView::MapLoaderView(Window& window)
    : View{window}
{
    this->init();
}


void MapLoaderView::init() {
    this->buildGUI();
    clearMapNameBoxWithPrompt();
}

void MapLoaderView::buildGUI() {
    createBackgroundFrom(config::bg::loader);
    createMainPanel();
    createButtons();
    createMapNameBox();
    createBadMapLabel();
}

void MapLoaderView::clearMapNameBoxWithPrompt() {
    this->promptToEnterMapName = true;
    const auto& mapNameBox = this->getView().getContainer()->get<tgui::EditBox>("mapNameBox");
    mapNameBox->setText({"Enter map name..."});
}

void MapLoaderView::clearMapNameBox() {
    this->getView().getContainer()->get<tgui::EditBox>("mapNameBox")->setText({});
}

void MapLoaderView::setBadMapLabelVisible(bool visibilityStatus) {
    this->getView().getContainer()->get<tgui::Label>("badMapLabel")->setVisible(visibilityStatus);
}

void MapLoaderView::animateBadMapLabel() {
    const auto& badMapLabel = this->getView().getContainer()->get<tgui::Label>("badMapLabel");
    badMapLabel->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(300));
}

std::string MapLoaderView::getMapName() const {
    return this->getView().getContainer()->get<tgui::EditBox>("mapNameBox")->getText().toAnsiString();
}

void MapLoaderView::setPromptToEnter(bool status) {
    promptToEnterMapName = status;
}

bool MapLoaderView::isPromptToEnter() const {
    return promptToEnterMapName;
}

void MapLoaderView::createMainPanel() {
    auto mainPanel = tgui::Panel::create({config.width + 22, 375});

    mainPanel->setPosition(184,107);
    mainPanel->getRenderer()->setBackgroundColor(tgui::Color::Black);
    mainPanel->setInheritedOpacity(0.3);
    mainPanel->getRenderer()->setBorders({2, 2, 2, 2});
    mainPanel->getRenderer()->setBorderColor(tgui::Color::White);

    view.add(mainPanel);
}

void MapLoaderView::createButtons() {
    for (auto i{0u}; auto btn : Loader::Buttons) {
        const auto& btnName = loaderConfig.widgetsNames[btn];
        widgets.emplace_back(tgui::Button::create(btnName));

        this->loadWidget(widgets[i]);
        ++i;
    }
}

void MapLoaderView::loadWidget(tgui::Widget::Ptr& widget) {
    if (buttonsCounter == 1) buttonsCounter += 2; ///< so there is a wide gap between buttons

    config.prepare(widget);
    widget->setPosition(view.getTarget()->getSize().x / 2 - Gui::Config<>::width / 2,
                        180 + 60 * buttonsCounter);
    buttonsCounter++;
    view.add(widget);
}

void MapLoaderView::createMapNameBox() {
    auto mapNameBox = tgui::EditBox::create();

    mapNameBox->setSize(config.width, config.height);
    mapNameBox->setTextSize(config.textSize);
    mapNameBox->getRenderer()->setTextColor(loaderConfig.mapNameColor);
    mapNameBox->setPosition(tgui::bindLeft(widgets[to_underlying(Loader::Btn::loadMap)]),
                            tgui::bindTop (widgets[to_underlying(Loader::Btn::loadMap)]) - 10 - config.height);
    mapNameBox->setInheritedFont(config.font);

    view.add(mapNameBox, "mapNameBox");
}

void MapLoaderView::createBadMapLabel() {
    auto badMapLabel = tgui::Label::create("No such file!");

    badMapLabel->setTextSize(config.textSize - 5);
    badMapLabel->setPosition(22, 132);
    badMapLabel->getRenderer()->setTextColor(tgui::Color{255, 0, 0});
    badMapLabel->setVisible(false);
    badMapLabel->setInheritedFont(config.font);

    view.add(badMapLabel, "badMapLabel");
}
