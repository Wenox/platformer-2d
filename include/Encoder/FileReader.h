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
    /** Note: basic_ifstream has copy ctor/copy assignment explicitly deleted */


    auto& getFile() const {
        return file;
    }

    auto& getFileName() const {
        return fileName;
    }

    auto& getData() const {
        return data;
    }

    auto& getDataRaw() const {
        return data.get();
    }

    auto& getDataSize() const {
        return dataSize;
    }

    bool isOpened() const {
        return file.is_open();
    }

protected:
    explicit FileReader(const std::string& name, const std::ios_base::openmode& mode = std::ifstream::in)
        : fileName{name}
        , file{name, mode}
    {}

    std::string  fileName;
    std::ifstream file;

    std::vector<T> data{};
    unsigned       dataSize{};
};

