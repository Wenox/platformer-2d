#pragma once

#include "FileReader.h"

struct Color {
    uint8_t blue;
    uint8_t green;
    uint8_t red;

    Color() = default;

    Color(uint8_t blue, uint8_t green, uint8_t red)
            :blue{blue},
             green{green},
             red{red}
    {
    }

    friend std::istream& operator>>(std::istream& input, Color& color) {
        input >> color.blue;
        input >> color.green;
        input >> color.red;
        return input;
    }

    bool operator<(const Color& other) const {
        return std::tie(blue, green, red) < std::tie(other.blue, other.green, other.red);
    }
};


class BmpReader final : public FileReader<Color>
{
public:
    explicit BmpReader(const std::string& name,
                       const std::ios_base::openmode& mode = std::ifstream::ate | std::ifstream::binary);

    virtual void readFile();

    int getPixelsCount() const;

    virtual ~BmpReader() = default;
    BmpReader(const BmpReader&) = default;
    BmpReader(BmpReader&&) = default;
    BmpReader& operator=(const BmpReader&) = default;
    BmpReader& operator=(BmpReader&&) = default;

    void debugPrint() const;

private:
    void readWidth();
    void readHeight();
    void readPixels();

    int32_t width{};
    int32_t height{};
    int pixelsCount{};

    static constexpr auto widthOffset{18};
    static constexpr auto heightOffset{22};
    static constexpr auto dataOffset{54};
    static constexpr auto bytesPerPixel{3};
};
