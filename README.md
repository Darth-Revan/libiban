# libiban
A C++ library for handling IBAN numbers

**WARNING** This software is currently work-in-progress and is not ready for use.

## Building

The project is based on CMake. To build the library itself, invoke the following
commands in the project's directory:

```
mkdir build
cd build
cmake ..
make libiban
```

For building the tests change the target of _make_ to `libiban_test`.

In order to build the documentation with _Doxygen_, change the target of _make_ to `doc`.
This will create a full API documentation in a directory _doc_ inside the
build directory.

## License

This software is released under the terms of the MIT License. See the
file [LICENSE](https://github.com/Darth-Revan/libiban/blob/master/LICENSE)
for the the full license text.