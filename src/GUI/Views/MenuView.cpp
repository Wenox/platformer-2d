#include "Consts.h"
#include "MenuView.h"


MenuView::MenuView(Window& window)
    : View{window}
{
    this->init();
}

void MenuView::init() {
    this->buildGUI();
}

void MenuView::buildGUI() {
    createBackgroundFrom(consts::bg::menu);
    createBackgroundPanel();

    for (auto i{0u}; auto btn : Menu::Buttons) {
        const auto &btnName = menuConfig.widgetsNames[btn];
        widgets.emplace_back(tgui::Button::create(btnName));

        this->loadWidget(widgets[i]);
        ++i;
    }

}

void MenuView::loadWidget(tgui::Widget::Ptr& widget) {
    config.prepare(widget);
    widget->setPosition({view.getTarget()->getSize().x / 2 - Gui::Config<>::width / 2,
                         Menu::Config::offsetY + view.getTarget()->getSize().y / 9 * ++buttonsCounter});
    view.add(widget);
}

void MenuView::createBackgroundPanel() {
    auto panelBorder = tgui::Panel::create({config.width + 22, 330});
    panelBorder->setPosition(184,96);
    panelBorder->getRenderer()->setBackgroundColor(tgui::Color::White);
    panelBorder->setInheritedOpacity(0.35);
    panelBorder->getRenderer()->setBorders({1, 1, 1, 1});
    panelBorder->getRenderer()->setBorderColor(tgui::Color::Black);
    view.add(panelBorder);
}