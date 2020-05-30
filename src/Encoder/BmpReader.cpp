#include <Consts.h>
#include "BmpReader.h"


BmpReader::BmpReader(const std::string& name,
                     const std::ios_base::openmode& mode)
        : FileReader{name, mode}
{
    readFile();
}

void BmpReader::readFile() {
    if (isOpened()) {
        if constexpr (consts::blocksCountWidth % 4 != 0) {
            throw std::runtime_error("Width has to be a multiple of 4");
        }
//        readWidth();
//        readHeight();
        readPixels();
    }
    else {
        throw std::runtime_error("Failed to open " + fileName);
    }
}

void BmpReader::readWidth() {
    file.seekg(widthOffset);
    width = file.get();
    if (width != consts::blocksCountWidth) {
        throw std::runtime_error("BMP width is " + std::to_string(width) + " but should be " + std::to_string(consts::blocksCountWidth));
    }
}

void BmpReader::readHeight() {
    file.seekg(heightOffset);
    height = file.get();
    if (height != consts::blocksCountHeight) {
        throw std::runtime_error("BMP height is " + std::to_string(height) + " but should be " + std::to_string(consts::blocksCountHeight));
    }
}

void BmpReader::readPixels() {
    pixelsCount = width * height;
    dataSize = pixelsCount * bytesPerPixel;

    file.seekg(dataOffset);



    PixelColor pixelColor{};
    while (file >> pixelColor) {
        data.emplace_back(pixelColor);
    }
}

int BmpReader::getPixelsCount() const {
    return pixelsCount;
}

void BmpReader::debugPrint() const {
    std::cout << "BMP width: " <<  width << std::endl;
    std::cout << "BMP height: " << height << std::endl;

    for (int i = 0; i < pixelsCount; i++) {
        std::cout << "Pixel " << i << ": "
                  << (uint16_t) data[i].blue << " "
                  << (uint16_t) data[i].green << " "
                  << (uint16_t) data[i].red << std::endl;
    }
}

