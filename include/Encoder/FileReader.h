#pragma once

#include <fstream>
#include <iostream>
#include <vector>


template <typename T>
class FileReader {
public:

    virtual void readFile() = 0;

    auto& getData() {
        return data;
    }

    virtual ~FileReader() = default;
    FileReader(FileReader&&) noexcept = default;
    FileReader& operator=(FileReader&&) noexcept = default;


    auto& getData() const {
        return data;
    }

    bool isOpened() const {
        return file.is_open();
    }

protected:
    explicit FileReader(const std::string& name, const std::ios_base::openmode& mode = std::ifstream::in)
            : fileName{name}
            , file{name, mode}
    {}

    std::string    fileName;
    std::ifstream  file;
    std::vector<T> data{};
};

