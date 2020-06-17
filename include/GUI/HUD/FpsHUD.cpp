#include "FpsHUD.h"

FpsHUD::FpsHUD() {
    this->setFont();
    this->setFps();
}

void FpsHUD::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(fps, states);
}

void FpsHUD::setValue(const std::string& fpsValue) {
    fps.setString(fpsValue);
}

void FpsHUD::setFont() {
    if (!font.loadFromFile("../resources/CascadiaCode.ttf"))
        throw MissingFont{"FpsHUD: CascadiaCode.ttf missing"};
}

void FpsHUD::setFps() {
    fps.setFont(font);
    fps.setCharacterSize(36);
    fps.setPosition(0, 960);
    fps.setFillColor(sf::Color::Yellow);
    fps.setOutlineColor(sf::Color::Black);
    fps.setOutlineThickness(1);
}