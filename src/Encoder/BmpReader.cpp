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
    std::cout << fileName << " width is: " << width << std::endl;
//    if (consts::blocksCountWidth % 4 != 0) {
//        throw std::runtime_error("Width has to be a multiple of 4");
//    }
}

void BmpReader::readHeight() {
    file.seekg(heightOffset);
    height = file.get();
    /*
    if (height != consts::blocksCountHeight) {
        throw std::runtime_error("BMP height is " + std::to_string(height) + " but should be " + std::to_string(consts::blocksCountHeight));
    }*/
    std::cout << fileName << " height is: " << height << std::endl;
}

void BmpReader::readPixels() {
    pixelsCount = width * height;
    dataSize = pixelsCount * bytesPerPixel;

    file.seekg(dataOffset);

    PixelColor pixelColor{};
    while (file >> pixelColor) {
        data.emplace_back(pixelColor);
    }

    consts::blocksCountWidth  = this->width;
    consts::blocksCountHeight = this->height;
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
