#include "PausedView.h"


PausedView::PausedView(Window& window)
    : View{window}
{
    this->init();
}

void PausedView::init() {
    this->buildGUI();
}

void PausedView::buildGUI() {
    /** todo: try removing bg from PausedState and use it here instead */

    auto panelBorder = tgui::Panel::create({config.width + 22, 205});
    panelBorder->setPosition(184,330);
    panelBorder->getRenderer()->setBackgroundColor(tgui::Color::Magenta);
    panelBorder->setInheritedOpacity(0.25);
    panelBorder->getRenderer()->setBorders({2, 2, 2, 2});
    panelBorder->getRenderer()->setBorderColor(tgui::Color::Black);
    view.add(panelBorder);

    auto bg = tgui::Picture::create(tgui::Texture{"../resources/PausedBGMain.png"});
    view.add(bg, "pausedBg");

    for (auto i{0u}; auto btn : Paused::Buttons) {
        const auto& btnName = menuConfig.widgetsNames[btn];
        widgets.emplace_back(tgui::Button::create(btnName));

        this->loadWidget(widgets[i]);
        ++i;
    }
}

void PausedView::loadWidget(tgui::Widget::Ptr& widget) {
    config.prepare(widget);
    widget->setPosition({view.getTarget()->getSize().x / 2 - Gui::Config<>::width / 2,
                         Paused::Config::offsetY + view.getTarget()->getSize().y / 9 * ++buttonsCounter});
    view.add(widget);
}