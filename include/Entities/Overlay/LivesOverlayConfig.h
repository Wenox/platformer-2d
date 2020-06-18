#pragma once

#include <SFML/Graphics/Color.hpp>

namespace lives {
    constexpr auto count = 3;
    constexpr auto boxSide = 50.0f;

    const sf::Color fillColor = sf::Color{255, 255, 255, 140}; /** semi-transparent white */
    const sf::Color borderColor = sf::Color::Red;

    constexpr auto borderThickness = 2;
    constexpr auto borderOffsetX = 15;
    constexpr auto borderOffsetY = 15;
    constexpr auto heartOffsetX  = 25;
    constexpr auto heartOffsetY  = 25;
}