#pragma once

#include "FileReader.h"
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
};
