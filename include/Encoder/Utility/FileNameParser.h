#pragma once

#include <regex>
#include <iostream>

class FileNameParser {
public:
    explicit FileNameParser(std::string fileName) : fileName{fileName} {
        try {
            re.assign(fileNamePattern.data());
        }
        catch(const std::regex_error& e) {
            std::cerr << "Bad pattern: " << fileNamePattern << std::endl;
            std::cerr << e.what() << std::endl;
        }
    }

    bool isNameCorrect() {
        return std::regex_match(fileName, result, re);
    }

    bool isBmp() const {
        return result.str(1) == std::string("bmp");
    }

    bool isTxt() const {
        return result.str(1) == std::string("txt");
    }

private:
    std::string fileName;
    std::regex re{};
    constexpr static std::string_view fileNamePattern = R"(.+?\.(bmp|txt))";
    std::smatch result{};
};


