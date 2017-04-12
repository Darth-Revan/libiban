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
 * \file        libiban.cpp
 * \brief       Main source file for \p libiban
 * \author      Kevin Kirchner
 * \date        2017
 * \copyright   MIT LICENSE
 *
 * This source file is the main source file for \p libiban and implements the
 * classes and functions of the library.
 */

#include <iostream>
#include "libiban.h"
#include "utils.h"

namespace IBAN {

    /**
     * Constructor of \p IBANParseException.
     *
     * @param iban The IBAN string causing the exception
     */
    IBANParseException::IBANParseException(const std::string &iban) noexcept :
            m_iban(iban) {
        m_message = "Cannot parse IBAN " + m_iban;
    }

    /**
     * Destructor of \p IBANParseException
     */
    IBANParseException::~IBANParseException() {}

    /**
     * Overrides the function \p what() for this exception and returns a
     * string describing the error.
     *
     * @return A string describing the error
     */
    const char *IBANParseException::what() const noexcept {
        return m_message.c_str();
    }

    /**
     * Implements assignment operator.
     *
     * @param other The other instance to assign
     * @return An instance of \p IBAN
     */
    IBAN& IBAN::operator=(IBAN other) {
        IBAN temp(other);
        swap(*this, temp);
        return *this;
    }

    /**
     * Tries to create a new instance of \p IBAN from a string parameter. If
     * parsing fails, the methods throws an \p IBANParseException. This happens
     * if the string is too short to be an IBAN number or if it contains invalid
     * characters.
     *
     * Note that this does not guarantee the validity of the IBAN number. Call
     * \p validate() to test for validity.
     *
     * @param string The string to create an IBAN from
     * @return A new instance of \p IBAN
     */
    IBAN IBAN::createFromString(const std::string &string) {
        std::string s;
        std::string countryCode{}, accID{};
        size_t checkSum{};

        s = const_cast<std::string&>(string);
        trim(s);
        std::transform(s.begin(), s.end(), s.begin(), ::toupper);
        // too long or too short
        if (s.length() > 34 || s.length() < 5) {
            throw IBANParseException(string);
        }

        // first to chars are country code
        countryCode = s.substr(0, 2);
        if (!isalpha(countryCode[0]) || !isalpha(countryCode[1])) {
            throw IBANParseException(string);
        }
        // then two chars for the check sum
        try {
            checkSum = static_cast<size_t>(std::stoi(s.substr(2, 2)));
        } catch (const std::exception) {
            throw IBANParseException(string);
        }
        // rest is account ID
        accID = s.substr(4);
        for (auto ch : accID) {
            if (!isalnum(ch)) {
                throw IBANParseException(string);
            }
        }

        return IBAN(countryCode, accID, checkSum);
    }

    /**
     * Return the account identifier part of the IBAN number.
     *
     * @return The account identifier of the IBAN
     */
    std::string IBAN::getAccountIdentifier() const {
        return m_accountIdentifier;
    }

    /**
     * Return the checksum part of the IBAN number.
     *
     * @return The checksum of the IBAN
     */
    size_t IBAN::getChecksum() const {
        return m_checkSum;
    }

    /**
     * Return the country code part of the IBAN number.
     *
     * @return The country code of the IBAN
     */
    std::string IBAN::getCountryCode() const {
        return m_countryCode;
    }

    /**
     * Returns the machine friendly formatting of the IBAN number which does
     * not contain any spaces.
     *
     * @return Machine friendly representation of the IBAN
     */
    std::string IBAN::getMachineForm() {
        return m_countryCode + std::to_string(m_checkSum) + m_accountIdentifier;
    }

    /**
     * Returns the human readable formatting of the IBAN number which formats
     * the IBAN number into blocks of 4 characters.
     *
     * @return Human readable representation of the IBAN
     */
    std::string IBAN::getHumanReadable() {
        std::stringstream result("");
        result << m_countryCode << m_checkSum;
        for (size_t i = 0; i < m_accountIdentifier.length(); i += 5) {
            m_accountIdentifier.insert(i, 1, ' ');
        }
        result << m_accountIdentifier;
        return result.str();
    }
}
