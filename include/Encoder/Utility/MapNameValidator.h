#pragma once

#include <regex>
#include <iostream>
#include <fstream>


class MapNameValidator {
public:
    explicit MapNameValidator(std::string_view fileName);

    bool isValidFormat();
    bool exists() const;

    bool isBmp() const;
    bool isTxt() const;

private:
    const std::string_view fileName;

    std::regex re{};
    constexpr static std::string_view mapNamePattern = R"(.+?\.(bmp|txt))";

    std::match_results<std::string_view::const_iterator> match{};
};


