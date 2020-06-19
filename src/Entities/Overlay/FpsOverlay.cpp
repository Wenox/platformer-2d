#include "FpsOverlay.h"
#include "Configuration.h"


FpsOverlay::FpsOverlay() {
    this->setFont();
    this->setFps();
}

void FpsOverlay::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(fps, states);
}

void FpsOverlay::update(float dt) {
    fps.setString(calcCurrentFps(dt));
}

std::string FpsOverlay::calcCurrentFps(float dt) {
    return std::to_string(static_cast<int>(1 / dt));
}

void FpsOverlay::setFont() {
    if (!font.loadFromFile(config::widgetsFontName.data()))
        throw MissingFont{"FpsOverlay missing font: " + std::string(config::widgetsFontName.data())};
}

void FpsOverlay::setFps() {
    fps.setFont(font);
    fps.setCharacterSize(36);
    fps.setPosition(0, 960);
    fps.setFillColor(sf::Color::Yellow);
    fps.setOutlineColor(sf::Color::Black);
    fps.setOutlineThickness(1);
}