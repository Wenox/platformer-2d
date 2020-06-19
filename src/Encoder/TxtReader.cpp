#include "TxtReader.h"
#include "Configuration.h"


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
        std::stringstream ss{line};
        config::blocksCountWidth  = std::distance(std::istream_iterator<int>{ss}, std::istream_iterator<int>{});
        config::blocksCountHeight = rows;

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

bool TxtReader::isValidTxt() {
    /** Allocate the memory for raw txt data */
    file.seekg(0, std::ios::end);
    rawTxtData.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    /** Entire file is loaded into string */
    rawTxtData.assign((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());

    /** And checked if it indeed is a valid Txt file (white-space delimited numbers-only content) */
    std::string fullMatchPattern = R"((?:[[:space:]]*[[:digit:]]+[[:space:]]*)+)";
    std::regex re{fullMatchPattern};
    if (!std::regex_match(rawTxtData, re)) {
        std::cerr << "File " << fileName << " does not match the pattern!\n";
        return false;
    }

    return true;
}


