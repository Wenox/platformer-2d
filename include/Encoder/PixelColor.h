#pragma once

#include <tuple>

/** Bear in mind .bmp image format uses BGR color format, not RGB */

struct PixelColor {
    uint8_t blue;
    uint8_t green;
    uint8_t red;

    PixelColor() = default;

    PixelColor(uint8_t blue, uint8_t green, uint8_t red)
        : blue{blue}
        , green{green}
        , red{red}
    {}

    friend std::istream& operator>>(std::istream& input, PixelColor& color) {
        input >> color.blue;
        input >> color.green;
        input >> color.red;
        return input;
    }

    bool operator<(const PixelColor& other) const {
        return std::tie(blue, green, red) < std::tie(other.blue, other.green, other.red);
    }
};