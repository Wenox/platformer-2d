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
    FileReader(const FileReader&) = default;
    FileReader(FileReader&&) = default;
    FileReader& operator=(const FileReader&) = default;
    FileReader& operator=(FileReader&&) = default;


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

