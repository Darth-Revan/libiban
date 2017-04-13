/*
 * MIT License
 * Copyright (c) 2017 Kevin Kirchner
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * \file        utils.h
 * \brief       Header file declaring some useful utility functions
 * \author      Kevin Kirchner
 * \date        2017
 * \copyright   MIT LICENSE
 *
 * This header file declares some useful utility functions.
 */

#ifndef LIBIBAN_UTILS_H
#define LIBIBAN_UTILS_H

#include <string>
#include <algorithm>
#include <stdexcept>

/**
 * Trims a string and removes whitespace characters.
 *
 * @param s The string to trim
 * @return Trimmed version of the string
 */
inline std::string& trim(std::string& s) {
    s.erase(std::remove_if(s.begin(), s.end(),
                           [](char c) { return std::isspace(c); } ),
            s.end());
    return s;
}

/**
 * Generates and returns a randomly generated alphanumeric string.
 *
 * @param length The desired length of the string
 * @return Randomly generated alphanumeric string with length \p length
 */
std::string generateRandomString(const size_t length);

/**
 * Makes a string numerical by substituting letters by their position in
 * the alphabet plus \p add (default: 9). This is a common operation in
 * IBAN verification and calculation.
 * Throws a \p std::runtime_error if \p string contains non-alphanumerical
 * characters.
 *
 * @param string The string to convert
 * @param add An integer value to add to the value of a letter (default: 9)
 * @return Copy of the converted string
 * @throws runtime_error If \p string contains non-alphanumerical characters
 */
inline std::string makeNumerical(const std::string &string, const size_t add = 9) {
    std::string numeric = "";
    for (auto& ch : string) {
        if (std::isdigit(ch)) {
            numeric.push_back(ch);
        } else if (std::isalpha(ch)) {
            // get position in latin alphabet and add \p add
            numeric += std::to_string( (31 & ch) + add );
        } else {
            throw std::runtime_error("Unexpected character: " + std::to_string(ch));
        }
    }
    return numeric;
}


#endif //LIBIBAN_UTILS_H
