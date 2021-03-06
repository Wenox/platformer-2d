#include "BmpReader.h"
#include "Configuration.h"


BmpReader::BmpReader(const std::string& name,
                     const std::ios_base::openmode& mode)
        : FileReader{name, mode}
{
    readFile();
}

void BmpReader::readFile() {
    if (isOpened()) {
        readWidth();
        readHeight();
        readPixels();
    }
    else {
        throw std::runtime_error("Failed to open " + fileName);
    }
}

void BmpReader::readWidth() {
    file.seekg(widthOffset);
    width = file.get();
}

void BmpReader::readHeight() {
    file.seekg(heightOffset);
    height = file.get();
}

void BmpReader::readPixels() {
    pixelsCount = width * height;

    file.seekg(dataOffset);

    PixelColor pixelColor{};
    while (file >> pixelColor) {
        data.emplace_back(pixelColor);
    }

    config::blocksCountWidth  = this->width;
    config::blocksCountHeight = this->height;
}

int BmpReader::getPixelsCount() const {
    return pixelsCount;
}

void BmpReader::debugPrint() const {
    std::cout << "BMP width: " <<  width << std::endl;
    std::cout << "BMP height: " << height << std::endl;

    for (int i = 0; i < pixelsCount; i++) {
        std::cout << "Pixel " << i << ": "
                  << static_cast<uint16_t>(data[i].blue)  << " "
                  << static_cast<uint16_t>(data[i].green) << " "
                  << static_cast<uint16_t>(data[i].red)   << std::endl;
    }
}