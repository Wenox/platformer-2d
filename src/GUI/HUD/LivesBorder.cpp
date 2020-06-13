#include "LivesBorder.h"


LivesBorder::LivesBorder(const sf::Rect<float>& viewport)
    : viewport{viewport}
{
    this->setBorder();
}

void LivesBorder::setBorder() {
    this->border.setSize(sf::Vector2f{lives::count * lives::boxSide, lives::boxSide});
    this->border.setOutlineColor(lives::borderColor);
    this->border.setOutlineThickness(lives::borderThickness);
    this->border.setFillColor(lives::fillColor);
    this->border.setPosition(this->viewport.left + lives::borderOffsetX, this->viewport.top + lives::borderOffsetY);
}

void LivesBorder::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(border, states);
}