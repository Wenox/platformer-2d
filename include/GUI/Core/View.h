#pragma once

#include <TGUI/TGUI.hpp>
#include "Window.h"


template <typename TWidgetPtr = tgui::Widget::Ptr>
class View {
protected:
    tgui::Gui view;
    int buttonsCounter{0};

    virtual void buildGUI() = 0;

public:
    std::vector<TWidgetPtr> widgets;

    explicit View(Window& window)
        : view{window.getWindow()}
    {}

    virtual void handleEvent(std::queue<sf::Event>& events) {
        while (!events.empty()) {
            view.handleEvent(events.front());
            events.pop();
        }
    }

    virtual void draw() {
        view.draw();
    }

    void createBackground(std::string_view backgroundName) {
        view.add(tgui::Picture::create(backgroundName.data()));
    }

    auto& getView() const {
        return view;
    }

    virtual ~View() = default;
    View(const View&) = default;
    View(View&&) noexcept = default;
    View& operator=(const View&) = default;
    View& operator=(View&&) noexcept = default;
};