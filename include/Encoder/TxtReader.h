/** @file */
#pragma once

#include "FileReader.h"
#include <regex>

/** \class TxtReader
 *
 *  \ingroup Encoder
 *
 *  \brief Reads the .txt file into the vector of int.
 *
 *  \brief This would be a preferred way of loading maps, once the map editor is fully developed <em>(out of CP4 scope)</em>.
 *
 *  */
class TxtReader final : public FileReader<int>
{
public:

    /** \brief Create a TxtReader.
     *
     * @param name Name of the file to be read.
     * @param mode Open mode introduced as a generalization.
     *
     * Reads the .txt file data.
     *
     * */
    explicit TxtReader(const std::string& name,
                       const std::ios_base::openmode& mode = std::ifstream::ate | std::ifstream::binary);

    /** \bief Read the file data into the PixelColor vector.
     *
     * Implements the pure virtual method of FileReader<T>.
     *
     * */
    void readFile() override;

    /** \brief Default Virtual constructor. */
    ~TxtReader() override = default;
    /** \brief Enable move operations. */
    TxtReader(TxtReader&&) noexcept = default;
    /** \brief Enable move operations. */
    TxtReader& operator=(TxtReader&&) noexcept = default;

    /** \brief Print formatted file content debug info. */
    void debugPrint() const;

private:
    std::string rawTxtData{}; ///< Used for analyzing if a file is a valid .txt.

    /** \brief Analyzes if a .txt file is valid. It is valid only if it is well-formatted.
     *
     * Uses regular expessions underneath.
     *
     * \note A file is valid if it matches <em>R"((?:[[:space:]]*[[:digit:]]+[[:space:]]*)+)"</em> pattern.
     *
     * @returns Was this a valid txt file?
     * */
    bool isValidTxt();
};
