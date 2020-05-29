#include <Consts.h>
#include "TxtReader.h"


TxtReader::TxtReader(const std::string& name,
                     const std::ios_base::openmode& mode)
        : FileReader{name, mode}
{
    if (isValidTxt()) {
        readFile();
    }
}

void TxtReader::readFile() {
    std::cout << "OpenSuccess: " << this->isOpened() << std::endl;
    if (isOpened()) {
        if constexpr (consts::blocksCountWidth % 4 != 0) {
            throw std::runtime_error("Width has to be a multiple of 4");
        }

        int num;
        while (file >> num) {
            data.emplace_back(num);
        }
    }
    else {
        throw std::runtime_error("Failed to open " + fileName);
    }
}

void TxtReader::debugPrint() const {
    for (auto item : data) {
        std::cout << item << " ";
    } std::cout << std::endl;
}

