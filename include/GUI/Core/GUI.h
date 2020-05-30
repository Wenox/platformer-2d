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

    virtual void handleEvent(std::queue<sf::Event>& events) {
        while (!events.empty()) {
            gui.handleEvent(events.front());
            events.pop();
        }
    }

    virtual void draw() {
        gui.draw();
    }

    auto& getGui() {
        return gui;
    }

    virtual ~GUI() = default;
    ///* todo: consider Ro5 */
};