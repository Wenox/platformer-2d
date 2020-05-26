#pragma once

#include <TGUI/TGUI.hpp>


template <typename TWidgetPtr = tgui::Widget::Ptr>
class GUI {
protected:
    tgui::Gui gui;

    virtual void buildGUI() = 0;

public:
    std::vector<TWidgetPtr> widgets;

    explicit GUI(Window& window)
    : gui{window.getWindow()}
    {}

    virtual void handleEvent(sf::Event e) {
        gui.handleEvent(e);
    }

    virtual void draw() {
        gui.draw();
    }

    virtual ~GUI() = default;
    ///* todo: consider Ro5 */
};