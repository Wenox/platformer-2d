#include "MapLoaderGUI.h"

MapLoaderGUI::MapLoaderGUI(Window& window)
    : GUI{window}
{
    this->init();
}


void MapLoaderGUI::init() {
    this->buildGUI();
}


void MapLoaderGUI::buildGUI() {
    /** background */
    gui.add(tgui::Picture::create("../resources/mapLoader.jpg"));

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
    mapNameBox->setPosition(tgui::bindLeft(widgets[to_underlying(Loader::Btn::loadMap)]),
                         tgui::bindBottom(widgets[to_underlying(Loader::Btn::loadMap)]) + 10);
    gui.add(mapNameBox, "mapNameBox");


    /** label when entering bad map's name */
    auto badMapLabel = tgui::Label::create("No such file!");
    badMapLabel->setTextSize(config.textSize - 5);
    badMapLabel->setPosition(tgui::bindLeft(mapNameBox) - badMapLabel->getSize().x - 10, tgui::bindTop(mapNameBox) + 12);
    badMapLabel->getRenderer()->setTextColor(tgui::Color{255, 0, 0});
    badMapLabel->setVisible(false);

    gui.add(badMapLabel, "badMapLabel");
}


void MapLoaderGUI::loadWidget(tgui::Widget::Ptr& widget) {
    if (btnIndex == 2) ++btnIndex;

    config.prepare(widget);
    widget->setPosition(gui.getTarget()->getSize().x / 2 - Gui::Config<>::width / 2,
                        180 + 60 * btnIndex);
    btnIndex++;
    gui.add(widget);
}