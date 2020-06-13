#pragma once

#include <regex>
#include <iostream>
#include <fstream>


class FileNameParser {
public:
    explicit FileNameParser(std::string fileName);

    bool isValidFormat();
    bool exists() const;

    bool isBmp() const;
    bool isTxt() const;

private:
    std::string fileName;

    std::regex re{};
    constexpr static std::string_view fileNamePattern = R"(.+?\.(bmp|txt))";

    std::smatch result{};
};


