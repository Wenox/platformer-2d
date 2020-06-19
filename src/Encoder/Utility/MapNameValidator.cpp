/** @file */

#include "MapNameValidator.h"


MapNameValidator::MapNameValidator(std::string_view fileName)
    : fileName{fileName}
{
    try {
        re.assign(mapNamePattern.data());
    }
    catch (const std::regex_error& e) {
        std::cerr << "Bad pattern: " << mapNamePattern << std::endl;
        std::cerr << e.what() << std::endl;
    }
}

bool MapNameValidator::isValidFormat() {
    return std::regex_match(fileName.data(), match, re);
}

bool MapNameValidator::exists() const {
    std::ifstream file{fileName.data()};
    return file.good();
}

bool MapNameValidator::isBmp() const {
    return match.str(1) == std::string("bmp");
}

bool MapNameValidator::isTxt() const {
    return match.str(1) == std::string("txt");
}