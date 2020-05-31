#include <Consts.h>
#include "TxtReader.h"


TxtReader::TxtReader(const std::string& name,
                     const std::ios_base::openmode& mode)
        : FileReader{name, mode}
{
    if (isValidTxt()) {
        std::cout << "READ\n";
        readFile();
    }
}

void TxtReader::readFile() {
    std::cout << "OpenSuccess: " << this->isOpened() << std::endl;
    if (isOpened()) {
        if (consts::blocksCountWidth % 4 != 0) {
            throw std::runtime_error("Width has to be a multiple of 4");
        }

        file.seekg(0);
        int num;
        while (file >> num) {
            data.emplace_back(num);
        }

        consts::blocksCountHeight = 10; /** todo: count number of rows in a txt file */
        consts::blocksCountWidth = 10;  /** todo: count number of cols in a txt file */
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

