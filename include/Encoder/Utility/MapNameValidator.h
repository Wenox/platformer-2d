/** @file */

#pragma once



#include <regex>
#include <iostream>
#include <fstream>

/** \class MapNameValidator
 *
 *  \ingroup Encoder
 *
 *  \brief A utility class validating if a given map file name is valid.
 *
 *  \note
 *  A file is valid if:
 *    - it exists
 *    - is accessible
 *    - has correct file extension
 *
 *  Available file extensions:
 *    - .bmp
 *    - .txt
 *
 *  Uses regex to match file name against the pattern.
 *
 *
 * */
class MapNameValidator {
public:

    /** \brief Constructs a MapNameValidator of a given fileName.
     *
     * @param fileName File name of a given game map.
     *
     * Throws if a pattenr is incorrect, however, the pattern is known at compile time.
     *
     * \note C++ standard library regexes are compiled to FSA at run-time, even if it is already year 2020 as of <em>today</em>.
     *
     *
     * */
    explicit MapNameValidator(std::string_view fileName);

    /** C\brief hecks if given #fileName extension is a valid format.
     *
     * Currently supported game map files:
     *   - .bmp
     *   - .txt
     *
     * Matches the #fileName against regular expression #re generated from #mapNamePattern.
     *
     * @returns Is #fileName a valid map format (.bmp, .txt)?
     * */
    bool isValidFormat();

    /** \brief Checks if a given #fileName exists.
     *
     * @returns Does the file exist?
     *
     * */
    bool exists() const;

    /** \brief Check if a #fileName is a .bmp file. Called only if isValidFormat() was true.
     *
     * \note: File extension is stored as a first subexpression (index 1) inside #match.
     *
     * @returns Is #fileName a .bmp file?
     * */
    bool isBmp() const;
    /** \brief Check if a #fileName is a .txt file. Called only if isValidFormat() was true.
     *
     * \note: File extension is stored as a first subexpression (index 1) inside #match.
     *
     * @returns Is #fileName a .txt file?
     * */
    bool isTxt() const;

private:
    const std::string_view fileName; ///< \brief Map name.

    std::regex re{}; ///< \brief Run-time FSA compiled (!) evem if pattern is known at compile-time.
    constexpr static std::string_view mapNamePattern = R"(.+?\.(bmp|txt))"; ///< \brief Compile-time basic file matcher pattern.

    std::match_results<std::string_view::const_iterator> match{}; ///< \brief Stored match results.
};


