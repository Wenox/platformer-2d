#include "RestartView.h"
#include "Consts.h""


RestartView::RestartView(Window& window, ResourceManager& resourceManager)
    : View{window}
    , lostTexture{resourceManager.getTextures()[res::Texture::GameOver]}
    , wonTexture {resourceManager.getTextures()[res::Texture::GameWon]}
{
    this->init();
}

void RestartView::init() {
    this->buildGUI();

    this->setGameWonTexture();
    gameFinishedImage->setPosition(16, 16);
}

void RestartView::setGameWonTexture() {
    gameFinishedImage->getRenderer()->setTexture(wonTexture);
}

void RestartView::setGameLostTexture() {
    gameFinishedImage->getRenderer()->setTexture(lostTexture);
}

void RestartView::buildGUI() {
    createBackgroundFrom(consts::bg::restart);
    createPanels();
    createButtons();
    createGameFinishedImage();
}

void RestartView::createPanels() {
    createMainPanel();
    createButtonsPanel();
}


void RestartView::createMainPanel() {
    auto mainPanel = tgui::Panel::create({612, 484});

    mainPanel->setPosition(14,14);
    mainPanel->getRenderer()->setBackgroundColor(tgui::Color::Magenta);
    mainPanel->setInheritedOpacity(0.12);
    mainPanel->getRenderer()->setBorders({4, 4, 4, 4});
    mainPanel->getRenderer()->setBorderColor(tgui::Color::Black);

    view.add(mainPanel, "mainPanel");
}

void RestartView::createButtonsPanel() {
    auto btnPanel = tgui::Panel::create({533, 62});

    btnPanel->setPosition(restartConfig.offsetX - 6, restartConfig.offsetY - 6);
    btnPanel->getRenderer()->setBackgroundColor(tgui::Color::Magenta);
    btnPanel->setInheritedOpacity(0.2);
    btnPanel->getRenderer()->setBorders({2, 2, 2, 2});
    btnPanel->getRenderer()->setBorderColor(tgui::Color::White);

    view.add(btnPanel, "btnPanel");
}

void RestartView::createButtons() {
    for (auto i{0u}; auto btn : Restart::Buttons) {
        const auto &btnName = restartConfig.widgetsNames[btn];
        widgets.emplace_back(tgui::Button::create(btnName));

        this->loadWidget(widgets[i]);
        ++i;
    }
}

void RestartView::createGameFinishedImage() {
    gameFinishedImage = tgui::Picture::create(wonTexture);
    view.add(gameFinishedImage, "gameFinishedImage");
}

void RestartView::loadWidget(tgui::Widget::Ptr& widget) {
    config.prepare(widget);
    widget->setPosition({restartConfig.offsetX + (restartConfig.spacing + config.width) * buttonsCounter++,
                         restartConfig.offsetY});  /** todo: use Restart::Configs without instance of restartConfig */
    view.add(widget);
}