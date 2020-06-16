#include "MapLoaderGUI.h"

MapLoaderGUI::MapLoaderGUI(Window& window)
    : GUI{window}
{
    this->init();
}


void MapLoaderGUI::init() {
    this->buildGUI();
    clearMapNameBoxWithPrompt();
}


void MapLoaderGUI::buildGUI() {
    /** background */
    gui.add(tgui::Picture::create("../resources/mapLoader.jpg"));

    auto panelBorder = tgui::Panel::create({config.width + 22, 375});
    panelBorder->setPosition(184,
                             107);
    panelBorder->getRenderer()->setBackgroundColor(tgui::Color::Black);
    panelBorder->setInheritedOpacity(0.3);
    panelBorder->getRenderer()->setBorders({1, 1, 1, 1});
    panelBorder->getRenderer()->setBorderColor(tgui::Color::White);
    gui.add(panelBorder);

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
    gui.add(mapNameBox, "mapNameBox");


    /** label when entering bad map's name */
    auto badMapLabel = tgui::Label::create("No such file!");
    badMapLabel->setTextSize(config.textSize - 5);
    badMapLabel->setPosition(tgui::bindLeft(mapNameBox) - badMapLabel->getSize().x - 32, tgui::bindTop(mapNameBox) + 12);
    badMapLabel->getRenderer()->setTextColor(tgui::Color{255, 0, 0});
    badMapLabel->setVisible(false);
    badMapLabel->setInheritedFont(config.font);

    gui.add(badMapLabel, "badMapLabel");
}


void MapLoaderGUI::loadWidget(tgui::Widget::Ptr& widget) {
    if (btnIndex == 1) btnIndex += 2;

    config.prepare(widget);
    widget->setPosition(gui.getTarget()->getSize().x / 2 - Gui::Config<>::width / 2,
                        180 + 60 * btnIndex);
    btnIndex++;
    gui.add(widget);
}