/** @file */
#pragma once


#include "FileReader.h"
#include "PixelColor.h"

/** \class BmpReader
 *
 *  \ingroup Encoder
 *
 *  \brief Reads the .bmp file into the vector of PixelColor.
 *
 *  \warning Only .bmp files with width that is multiplier of **4** (e.g. 44 but not 45) are correctly encodeable into the World.
 *
 *  Valid .bmp dimensions [width x height]:
 *  - 40 x 23
 *  - 200 x 10
 *  - 404 x 303
 *
 *  Invalid .bmp dimensions [width x height]:
 *  - 101 x 40
 *  - 43 x 44
 *  - 501 x 10
 *
 *
 *  \note
 *  */
class BmpReader final : public FileReader<PixelColor>
{
public:

    /** \brief Create a BmpReader.
     *
     * @param name Name of the file to be read.
     * @param mode Open mode introduced as a generalization.
     *
     * Reads the .bmp file data.
     *
     * */
    explicit BmpReader(const std::string& name,
                       const std::ios_base::openmode& mode = std::ifstream::ate | std::ifstream::binary);

    /** \bief Read the file data into the PixelColor vector.
     *
     * Implements the pure virtual method of FileReader<T>.
     *
     * */
    void readFile() override;

    /** \brief Default Virtual constructor. */
    ~BmpReader() override = default;
    /** \brief Enable move operations. */
    BmpReader(BmpReader&&) noexcept = default;
    /** \brief Enable move operations. */
    BmpReader& operator=(BmpReader&&) noexcept = default;

    /** \brief Print formatted file content debug info. */
    void debugPrint() const;

private:
    /** \brief Read the .bmp width into #width. Peeks specific #widthOffset byte. */
    void readWidth();
    /** \brief Read the .bmp height into #height. Peeks specific #heightOffset byte. */
    void readHeight();

    /** \brief Reads the file PixelColor data once it was opened and its #width and #height were established. */
    void readPixels();

    int32_t width{};
    int32_t height{};
    int pixelsCount{};

    static constexpr auto widthOffset{18};
    static constexpr auto heightOffset{22};
    static constexpr auto dataOffset{54};
    static constexpr auto bytesPerPixel{3};
};
