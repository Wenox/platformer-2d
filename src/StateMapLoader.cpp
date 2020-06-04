#include "StateMapLoader.h"

void StateMapLoader::setGui() {
    gui.widgets[to_underlying(Loader::Btn::loadConfirm)]->connect("Pressed", [&]() {
        this->mapName = gui.getGui().getContainer()->get<tgui::EditBox>("editBox")->getText().toAnsiString();
        gui.getGui().getContainer()->get<tgui::EditBox>("editBox")->setText("");
        gui.getGui().getContainer()->get<tgui::Label>("editBoxLabel")->setTextSize(gui.config.textSize - 5);
        gui.getGui().getContainer()->get<tgui::Label>("editBoxLabel")->getRenderer()->setTextColor(
                tgui::Color{255, 0, 0});
        gui.getGui().getContainer()->get<tgui::Label>("editBoxLabel")->setText("No such file");
        gui.getGui().getContainer()->get<tgui::Label>("editBoxLabel")->showWithEffect(
                tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(300));
        gui.getGui().getContainer()->get<tgui::Label>("editBoxLabel")->setVisible(false);

        /** todo: to be cleaned up */
    });
}