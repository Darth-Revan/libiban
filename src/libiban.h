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
 * \file        libiban.h
 * \brief       Main header file for \p libiban
 * \author      Kevin Kirchner
 * \date        2017
 * \copyright   MIT LICENSE
 *
 * This header file is the main header file for \p libiban and declares the
 * classes and functions of the library.
 */

#ifndef LIBIBAN_LIBIBAN_H
#define LIBIBAN_LIBIBAN_H

#include <string>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <memory>

namespace IBAN {

    /*
typedef std::unordered_map<std::string, size_t> map_t;
typedef std::unique_ptr<map_t> pmap_t;

static const pmap_t p_countryCodes = pmap_t(new map_t({
      {"AL" , 28} , {"AD" , 24} , {"AT" , 20} , {"AZ" , 28 } ,
      {"BE" , 16} , {"BH" , 22} , {"BA" , 20} , {"BR" , 29 } ,
      {"BG" , 22} , {"CR" , 21} , {"HR" , 21} , {"CY" , 28 } ,
      {"CZ" , 24} , {"DK" , 18} , {"DO" , 28} , {"EE" , 20 } ,
      {"FO" , 18} , {"FI" , 18} , {"FR" , 27} , {"GE" , 22 } ,
      {"DE" , 22} , {"GI" , 23} , {"GR" , 27} , {"GL" , 18 } ,
      {"GT" , 28} , {"HU" , 28} , {"IS" , 26} , {"IE" , 22 } ,
      {"IL" , 23} , {"IT" , 27} , {"KZ" , 20} , {"KW" , 30 } ,
      {"LV" , 21} , {"LB" , 28} , {"LI" , 21} , {"LT" , 20 } ,
      {"LU" , 20} , {"MK" , 19} , {"MT" , 31} , {"MR" , 27 } ,
      {"MU" , 30} , {"MC" , 27} , {"MD" , 24} , {"ME" , 22 } ,
      {"NL" , 18} , {"NO" , 15} , {"PK" , 24} , {"PS" , 29 } ,
      {"PL" , 28} , {"PT" , 25} , {"RO" , 24} , {"SM" , 27 } ,
      {"SA" , 24} , {"RS" , 22} , {"SK" , 24} , {"SI" , 19 } ,
      {"ES" , 24} , {"SE" , 24} , {"CH" , 21} , {"TN" , 24 } ,
      {"TR" , 26} , {"AE" , 23} , {"GB" , 22} , {"VG" , 24 }
}));
     */

/// Exception to be thrown when parsing an IBAN string fails
class IBANParseException : public std::exception {

private:
    /// Holds the IBAN number causing the error
    std::string m_iban;
    /// The exception message
    std::string m_message;

public:
    IBANParseException(const std::string& iban) noexcept;
    virtual ~IBANParseException();
    IBANParseException(const IBANParseException& other)=default;
    virtual const char* what() const noexcept;

};

/// Main class of the library
class IBAN {

private:
    std::string m_countryCode {};
    std::string m_accountIdentifier {};
    size_t m_checkSum {};
    IBAN(const std::string& cCode, const std::string& accId,
         const size_t checkSum) : m_countryCode(cCode),
                                  m_accountIdentifier(accId),
                                  m_checkSum(checkSum) {}

public:
    IBAN(const IBAN&)=default;
    ~IBAN() {}
    IBAN& operator=(IBAN other);
    bool operator==(const IBAN& other) const;
    bool operator!=(const IBAN& other) const;
    static IBAN createFromString(const std::string& string);
    std::string getCountryCode() const;
    std::string getAccountIdentifier() const;
    size_t getChecksum() const;
    std::string getHumanReadable();
    std::string getMachineForm();

    /**
     * Swaps \p first and \p second by swapping their member variables' values.
     *
     * @param first First instance of \p IBAN
     * @param second Second instance of \p IBAN
     */
    friend void swap(IBAN& first, IBAN& second) {
        using std::swap;
        swap(first.m_checkSum, second.m_checkSum);
        swap(first.m_accountIdentifier, second.m_accountIdentifier);
        swap(first.m_countryCode, second.m_countryCode);
    }

}; // end of class IBAN

/**
 * Overloads the comparison operator ==.
 *
 * @param other The object to compare with
 * @return \p true if both objects are equal, \p false otherwise
 */
inline bool IBAN::operator==(const IBAN &other) const {
    return ((this->getCountryCode() == other.getCountryCode()) &&
            (this->getChecksum() == other.getChecksum()) &&
            (this->getAccountIdentifier() == other.getAccountIdentifier()));
}

/**
 * Overloads the comparison operator !=.
 *
 * @param other The object to compare with
 * @return \p true if the objects are not equal, \p false if they are equal
 */
inline bool IBAN::operator!=(const IBAN &other) const {
    return !(*this == other);
}

/**
 * Implements assignment operator.
 *
 * @param other The other instance to assign
 * @return An instance of \p IBAN
 */
inline IBAN& IBAN::operator=(IBAN other) {
    IBAN temp(other);
    swap(*this, temp);
    return *this;
}

} // end of namespace IBAN

#endif //LIBIBAN_LIBIBAN_H
