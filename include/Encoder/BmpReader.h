#pragma once

#include "FileReader.h"
#include "PixelColor.h"


class BmpReader final : public FileReader<PixelColor>
{
public:
    explicit BmpReader(const std::string& name,
                       const std::ios_base::openmode& mode = std::ifstream::ate | std::ifstream::binary);

    void readFile() override;

    int getPixelsCount() const;

    ~BmpReader() override = default;
    BmpReader(BmpReader&&) = default;
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
