#pragma once

#include <memory>
#include <fstream>


template <typename T>
class FileReader {
public:
    virtual void readData() = 0;


    auto& getData() {
        return data;
    }


    virtual ~FileReader() = default;
    /** Ro5 */

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
        : file{name, mode}
        , fileName{name}
    {}

    bool openSuccess() const {
        if (file) {
            return true;
        }
    }



    std::fstream file;
    std::string  fileName;

    std::unique_ptr<T[]> data{};
    unsigned     dataSize{};
};

