tila [![Build Status][travis-img]][travis-link] [![Coverage Status][coveralls-img]][coveralls-link] [![Documentation][docs-img]][docs-link]
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

[CMake][cmake] for building. [Check][check] for testing. [LCOV][lcov] for test coverage.

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

[travis-img]: https://img.shields.io/travis/JuhaniImberg/tila.svg?style=flat-square
[travis-link]: https://travis-ci.org/JuhaniImberg/tila
[coveralls-img]: https://img.shields.io/coveralls/JuhaniImberg/tila.svg?style=flat-square
[coveralls-link]: https://coveralls.io/r/JuhaniImberg/tila?branch=master
[docs-img]: https://img.shields.io/badge/docs-yep-brightgreen.svg?style=flat-square
[docs-link]: http://ahdoc.pieso.me/JuhaniImberg/tila/index.html
[cmake]: http://www.cmake.org/
[check]: http://check.sourceforge.net/
[lcov]: http://ltp.sourceforge.net/coverage/lcov.php
