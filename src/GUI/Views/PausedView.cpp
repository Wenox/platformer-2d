#include "PausedView.h"
#include "Configuration.h"


PausedView::PausedView(Window& window)
    : View{window}
{
    this->init();
}

void PausedView::init() {
    this->buildGUI();
}

void PausedView::buildGUI() {
    createBackgroundFrom(config::bg::paused);
    createMainPanel();
    createPausedTextImage();
    createButtons();
}

void PausedView::createMainPanel() {
    auto mainPanel = tgui::Panel::create({config.width + 22, 205});

    mainPanel->setPosition(184, 330);
    mainPanel->getRenderer()->setBackgroundColor(tgui::Color::Magenta);
    mainPanel->setInheritedOpacity(0.25);
    mainPanel->getRenderer()->setBorders({2, 2, 2, 2});
    mainPanel->getRenderer()->setBorderColor(tgui::Color::Black);

    view.add(mainPanel);
}

void PausedView::createPausedTextImage() {
    auto bg = tgui::Picture::create(tgui::Texture{config::pausedTextImage.data()});
    view.add(bg, "pausedBg");
}

void PausedView::createButtons() {
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