tila [![Build Status](https://travis-ci.org/JuhaniImberg/tila.svg?branch=master)](https://travis-ci.org/JuhaniImberg/tila) [![Coverage Status](https://coveralls.io/repos/JuhaniImberg/tila/badge.svg?branch=master)](https://coveralls.io/r/JuhaniImberg/tila?branch=master)
====

Programming language interpreter for [Aineopintojen harjoitustyö: Tietorakenteet ja algoritmit](https://www.cs.helsinki.fi/courses/58161/2015/k/a/1).

| folder  | purpose                     |
|---------|-----------------------------|
| lib     | Actual code                 |
| cmd     | Command line interface      |
| test    | Tests for lib               |
| doc     | Documentation               |
| cmake   | Additional CMake modules    |
| build   | For building                |
| example | Examples of tila programs   |

Dependencies
------------

[CMake][0] for building. [Check][1] for testing. [LCOV][2] for test coverage.

Building
--------

    cd build
    cmake ..
    make

Testing
-------

    cd build
    cmake ..
    make all test

[0]: http://www.cmake.org/
[1]: http://check.sourceforge.net/
[2]: http://ltp.sourceforge.net/coverage/lcov.php
