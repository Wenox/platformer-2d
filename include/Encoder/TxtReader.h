#pragma once

#include "FileReader.h"
#include <regex>


class TxtReader final : public FileReader<int>
{
public:
    explicit TxtReader(const std::string& name,
                       const std::ios_base::openmode& mode = std::ifstream::ate | std::ifstream::binary);

    void readFile() override;

    ~TxtReader() override = default;
    TxtReader(TxtReader&&) = default;
    TxtReader& operator=(TxtReader&&) = default;

    void debugPrint() const;

private:
    std::string rawTxtData{};

    bool isValidTxt();
};
