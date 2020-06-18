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
    /** background */
    view.add(tgui::Picture::create("../resources/mapLoader.jpg"));

    auto panelBorder = tgui::Panel::create({config.width + 22, 375});
    panelBorder->setPosition(184,
                             107);
    panelBorder->getRenderer()->setBackgroundColor(tgui::Color::Black);
    panelBorder->setInheritedOpacity(0.3);
    panelBorder->getRenderer()->setBorders({1, 1, 1, 1});
    panelBorder->getRenderer()->setBorderColor(tgui::Color::White);
    view.add(panelBorder);

    /** buttons */
    for (auto i{0u}; auto btn : Loader::Buttons) {
        const auto& btnName = loaderConfig.widgetsNames[btn];
        widgets.emplace_back(tgui::Button::create(btnName));

        this->loadWidget(widgets[i]);
        ++i;
    }


    /** map name editBox */
    auto mapNameBox = tgui::EditBox::create();
    mapNameBox->setSize(config.width, config.height);
    mapNameBox->setTextSize(config.textSize);
    mapNameBox->getRenderer()->setTextColor(loaderConfig.mapNameColor);
    mapNameBox->setPosition(tgui::bindLeft(widgets[to_underlying(Loader::Btn::loadMap)]),
                            tgui::bindTop (widgets[to_underlying(Loader::Btn::loadMap)]) - 10 - config.height);
    mapNameBox->setInheritedFont(config.font);
    view.add(mapNameBox, "mapNameBox");


    /** label when entering bad map's name */
    auto badMapLabel = tgui::Label::create("No such file!");
    badMapLabel->setTextSize(config.textSize - 5);
    badMapLabel->setPosition(tgui::bindLeft(mapNameBox) - badMapLabel->getSize().x - 32, tgui::bindTop(mapNameBox) + 12);
    badMapLabel->getRenderer()->setTextColor(tgui::Color{255, 0, 0});
    badMapLabel->setVisible(false);
    badMapLabel->setInheritedFont(config.font);

    view.add(badMapLabel, "badMapLabel");
}


void MapLoaderView::loadWidget(tgui::Widget::Ptr& widget) {
    if (buttonsCounter == 1) buttonsCounter += 2;

    config.prepare(widget);
    widget->setPosition(view.getTarget()->getSize().x / 2 - Gui::Config<>::width / 2,
                        180 + 60 * buttonsCounter);
    buttonsCounter++;
    view.add(widget);
}

void MapLoaderView::clearMapNameBoxWithPrompt() {
    this->promptToEnter = true;
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
    promptToEnter = status;
}

bool MapLoaderView::isPromptToEnter() const {
    return promptToEnter;
}