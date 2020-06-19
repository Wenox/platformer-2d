/** @file */

#pragma once

#include <fstream>
#include <iostream>
#include <vector>

/** \class FileReader
 *
 *  \ingroup Encoder
 *
 *  \brief Abstract File Reader class template.
 *
 *  \note Inheriting classes: BmpReader and TxtReader.
 *
 *  */
template <typename T>
class FileReader {
public:

    /** \brief Pure virtual method to be overriden by deriving TxtReader and TxtReader. */
    virtual void readFile() = 0;

    /** Retrieve the data contained in a file.
     *
     * @returns std::vector<T> Vector of data of type T. */
    auto& getData() {
        return data;
    }

    /** \brief Default Virtual constructor. */
    virtual ~FileReader() = default;
    /** \brief Enable move operations. */
    FileReader(FileReader&&) noexcept = default;
    /** \brief Enable move operations. */
    FileReader& operator=(FileReader&&) noexcept = default;
    /** \note: basic_ifstream has copy ctor/copy assignment explicitly deleted. */


    auto& getData() const {
        return data;
    }


    /** \brief Check if a file is successfully opened.
     *
     * @returns Is file opened? */
    bool isOpened() const {
        return file.is_open();
    }

protected:
    explicit FileReader(const std::string& name, const std::ios_base::openmode& mode = std::ifstream::in)
        : fileName{name}
        , file{name, mode}
    {}

    std::string    fileName;  ///< \brief File name.
    std::ifstream  file;      ///< \brief File handle.
    std::vector<T> data{};    ///< \brief Containre for data of type T.
};

