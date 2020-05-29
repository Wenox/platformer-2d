#pragma once

#include "FileReader.h"
#include "PixelColor.h"
#include <regex>

class TxtReader final : public FileReader<int>
{
public:
    explicit TxtReader(const std::string& name,
                       const std::ios_base::openmode& mode = std::ifstream::ate | std::ifstream::binary);

    virtual void readFile();

    int getPixelsCount() const;

    virtual ~TxtReader() = default;
    TxtReader(const TxtReader&) = default;
    TxtReader(TxtReader&&) = default;
    TxtReader& operator=(const TxtReader&) = default;
    TxtReader& operator=(TxtReader&&) = default;

    void debugPrint() const;

private:
    std::string rawTxtData{};

    bool isValidTxt() {
        std::cout << "isOpened?: " << isOpened() << std::endl;

        /** Allocate the memory for raw txt data */
        file.seekg(0, std::ios::end);
        rawTxtData.reserve(file.tellg());
        file.seekg(0, std::ios::beg);

        /** Entire file is loaded into string*/
        rawTxtData.assign((std::istreambuf_iterator<char>(file)),
                   std::istreambuf_iterator<char>());

        /** And checked if it indeed is a valid Txt file (white-space delimited numbers-only content) */
        std::string fullMatchPattern = R"((?:[[:space:]]*[[:digit:]]+[[:space:]]*)+)";
        std::regex re{fullMatchPattern};
        if (!std::regex_match(rawTxtData, re)) {
            std::cout << "File does not match the pattern!\n";
            return false;
        }
        std::cout << "Correct file!\n";

        /** Temporary */
        std::string numberPattern = R"([[:blank:]]*[[:digit:]]+[[:blank:]]*)";
        std::regex myRe{numberPattern};
        for ( std::sregex_iterator it(std::begin(rawTxtData), std::end(rawTxtData), myRe)
            ; it != std::sregex_iterator{}
            ; ++it )
        {
            std::cout << "Match " << ++dataSize << ": " <<  (*it)[0] << std::endl;
        }
    }
};
