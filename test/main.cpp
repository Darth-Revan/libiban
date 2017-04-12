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
 * \file        main.cpp
 * \brief       The main test file and entry point for \p Catch
 * \author      Kevin Kirchner
 * \date        2017
 * \copyright   MIT LICENSE
 *
 * This file is the main test file for \p libiban and the entry point for
 * \p Catch.
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/libiban.h"
#include "../src/utils.h"

// Test case for trim function in utils.h
TEST_CASE("trim", "[utils]") {
    std::string test = "345 sdfnsf8 403  fsdfs \na\t asda";
    std::string test2 = "";
    std::string test3 = "\n\n \t asidas da4a sab sd94";
    std::string test4 = "abfOAHF48tadf";
    REQUIRE(trim(test) == "345sdfnsf8403fsdfsaasda");
    REQUIRE(trim(test2) == "");
    REQUIRE(trim(test3) == "asidasda4asabsd94");
    REQUIRE(trim(test4) == "abfOAHF48tadf");
}

// Test case for constructor
TEST_CASE("createFromString", "[libiban]") {
    IBAN::IBAN iban = IBAN::IBAN::createFromString("DE68 2105 0170 0012 3456 78");

    IBAN::IBAN iban2 = iban;
    REQUIRE(iban.getAccountIdentifier() == iban2.getAccountIdentifier());
    REQUIRE(iban.getCountryCode() == iban2.getCountryCode());
    REQUIRE(iban.getChecksum() == iban2.getChecksum());

    IBAN::IBAN iban3 = IBAN::IBAN::createFromString("DE68210501700012345678");
    REQUIRE(iban.getAccountIdentifier() == iban3.getAccountIdentifier());
    REQUIRE(iban.getCountryCode() == iban3.getCountryCode());
    REQUIRE(iban.getChecksum() == iban3.getChecksum());


    IBAN::IBAN iban4 = IBAN::IBAN::createFromString("AD43oh8445353ADF");
    REQUIRE(!iban4.getAccountIdentifier().empty());
    REQUIRE(!iban4.getCountryCode().empty());
    REQUIRE(iban4.getChecksum());

    try {
        IBAN::IBAN iban5 = IBAN::IBAN::createFromString("BLA");
    } catch (const IBAN::IBANParseException& ex) {
        REQUIRE(ex.what());
    }
    try {
        IBAN::IBAN iban6 = IBAN::IBAN::createFromString("B1af935395");
    } catch (const IBAN::IBANParseException& ex) {
        REQUIRE(ex.what());
    }
    try {
        IBAN::IBAN iban7 = IBAN::IBAN::createFromString("DE682105017000/2345678");
    } catch (const IBAN::IBANParseException& ex) {
        REQUIRE(ex.what());
    }
}

// Test case for comparison operators
TEST_CASE("Comparison operators", "[libiban]") {
    IBAN::IBAN iban = IBAN::IBAN::createFromString("DE68 2105 0170 0012 3456 78");
    IBAN::IBAN iban2 = IBAN::IBAN::createFromString("DE68210501700012345678");
    IBAN::IBAN iban3 = IBAN::IBAN::createFromString("LI4212345678901234567");
    REQUIRE(iban == iban2);
    REQUIRE(iban2 == iban);
    REQUIRE(iban != iban3);
    REQUIRE(iban3 != iban);
    REQUIRE(iban2 != iban3);
    REQUIRE(iban3 != iban2);
    REQUIRE(iban == iban);
}

// Test case for machine form output
TEST_CASE("getMachineForm", "[libiban]") {
    IBAN::IBAN iban = IBAN::IBAN::createFromString("DE68 2105 0170 0012 3456 78");
    REQUIRE(iban.getMachineForm() == "DE68210501700012345678");
    IBAN::IBAN iban2 = IBAN::IBAN::createFromString(" GB82 WEST 1234 5698 7654 32");
    REQUIRE(iban2.getMachineForm() == "GB82WEST12345698765432");
}

// Test case for human readable form output
TEST_CASE("getHumanReadable", "[libiban]") {
    IBAN::IBAN iban = IBAN::IBAN::createFromString("DE68 2105 0170 0012 3456 78");
    REQUIRE(iban.getHumanReadable() == "DE68 2105 0170 0012 3456 78");
    IBAN::IBAN iban2 = IBAN::IBAN::createFromString(" GB82 WEST 1234 5698 7654 32");
    REQUIRE(iban2.getHumanReadable() == "GB82 WEST 1234 5698 7654 32");
}
