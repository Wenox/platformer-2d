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
    if (isOpened()) {
        file.seekg(0);

        int num = 0, rows = 0;
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss{line};
            while (ss >> num) data.emplace_back(num);
            rows++;
        }

        consts::blocksCountWidth  = std::count_if(line.begin(), line.end(), [](char c){ return std::isspace(c); }) + 1;
        consts::blocksCountHeight = rows;
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

