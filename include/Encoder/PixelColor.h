/** @file */
#pragma once

#include <tuple>

/** \struct PixelColor
 *
 *  \ingroup Encoder
 *
 *  \brief Container for one .bmp BGR pixel.
 *
 * Used mostly for readability and convenience as opposed to necessity.
 *
 *  \note Bear in mind .bmp image format uses BGR color format, not RGB.
*  */

struct PixelColor {
    uint8_t blue;
    uint8_t green;
    uint8_t red;

    /** \brief Create default PixelColor. */
    PixelColor() = default;

    /** \brief Create PixelColor from given BGR parameters.
     * @param blue value 0-255
     * @param green value 0-255
     * @param red value 0-255 */
    PixelColor(uint8_t blue, uint8_t green, uint8_t red)
        : blue{blue}
        , green{green}
        , red{red}
    {}

    /** \brief Overload operator>> for convenience when reading .bmp into a data vector. */
    friend std::istream& operator>>(std::istream& input, PixelColor& color) {
        input >> color.blue;
        input >> color.green;
        input >> color.red;
        return input;
    }

    /** \brief Overload operator< so that PixelColor can be used as a map key inside Encoder<ReaderKey> class.*/
    bool operator<(const PixelColor& other) const {
        return std::tie(blue, green, red) < std::tie(other.blue, other.green, other.red);
    }
};