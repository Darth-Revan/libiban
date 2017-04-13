# libiban

A C++ library for handling IBAN numbers

## Building

The project is based on CMake. To build the library itself, invoke the following
commands in the project's directory:

```
mkdir build
cd build
cmake ..
make iban
```

For building the tests change the target of _make_ to `libiban_test`.

In order to build the documentation with _Doxygen_, change the target of _make_ to `doc`.
This will create a full API documentation in a directory _doc_ inside the
build directory.

The library is able to generate random IBAN numbers. To implement this random generation,
pseudo-random generators are used. In default configuration this random number generators
are implemented by _Boost Random_. Therefore, you will need to install this library on
your system to be able to build _libiban_ (CMake will refuse to compile if it can't find
it, of course). If you do not want to be dependent on _Boost Random_, please pass
the option `-DUSE_BOOST_RANDOM=OFF` to CMake as shown in the following:

```
mkdir build
cd build
cmake .. -DUSE_BOOST_RANDOM=OFF
make iban
```

As a result, the library will use the standard library function `rand()` instead of
_Boost Random_ and _libiban_ will not be linked against _Boost_.

---

**Note:** All IBAN numbers used for testing the validation function were
collected from [https://www.iban.com/structure.html](https://www.iban.com/structure.html)
and have been publicly available before. I did not intentionally incorporate any
IBAN number into the tests that may be linked to existing bank accounts.

---

**Note:** The library includes a function that is able to generate pseudo-random IBAN
numbers. This generated IBAN numbers are intended for testing purposes only (for generating
demo data for your application tests, for example). Do not use them for banking, as only banks
can generate and assign valid IBANs to be used in real transactions. Using a self-generated IBAN
for banking will most probably cause legal problems for you which will at least include loss of
the transaction.

**I am in no way responsible for any consequences resulting from inappropriate usage of the
generated numbers.**

---

## API

The library provides the following classes and functions:

**IBAN::createFromString(string)**

Generates a new instance of the base IBAN class from a string.

**IBAN::generateIBAN(countryCode)**

Generates a valid random IBAN number for the country specified by _countryCode_.

**IBAN::getCountryCode()**

Returns the IBAN's country code.

**IBAN::getBBAN()**

Returns the Basic Bank Account Number of the IBAN.

**IBAN::getChecksum()**

Returns the IBAN's checksum.

**IBAN::getHumanReadable()**

Returns a string representing the IBAN and groups the IBAN's characters into
groups of four for easier reading.

**IBAN::getMachineForm()**

Returns a string representing the IBAN without any spaces.

**IBAN::validate()**

Validates the IBAN and returns a boolean flag indicating the validation result.

For more detailed information on the API, build the Doxygen documentation as described above
and read it :-).

## Usage

In order to use the library simply include the header file and link your executable against
_libiban_ by adding `-liban` to your compiler flags. Note that _libiban_ requires compiling
with the C++11 standard or newer.

#### Example

The following code snippet shows an example on how to use _libiban_.

```
#include "libiban.h"
#include <iostream>

int main() {
    auto iban = IBAN::IBAN::createFromString("DE68210501700012345678");

    if (iban.validate()) {
        std::cout << iban.getHumanReadable() << std::endl;
        std::cout << iban.getCountryCode() << std::endl;
    }
}
```

The output is

```
DE68 2105 0170 0012 3456 78
DE
```

## License

This software is released under the terms of the MIT License. See the
file [LICENSE](https://github.com/Darth-Revan/libiban/blob/master/LICENSE)
for the the full license text.