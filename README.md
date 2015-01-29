tila [![Build Status][travis-img]][travis-link] [![Coverage Status][coveralls-img]][coveralls-link] [![Documentation][docs-img]][docs-link]
====


| [Automated tests][travis-link] | [Code coverage status][coveralls-link] | [Rendered documentation][docs-link] |
| ------------------------------ | -------------------------------------- | ----------------------------------- |

Programming language interpreter for [Aineopintojen harjoitustyö: Tietorakenteet ja algoritmit][course-link].

Progress
--------

- [x] Tokenizer
- [ ] Base parser
  - [x] Basic stuff
  - [ ] Whitespace
- [ ] Sub parsers
  - [x] Identifier
  - [x] Assign
  - [x] Number
  - [ ] The rest
- [ ] Abstract syntax tree
- [ ] Environment
- [ ] Built in library

Folder structure
----------------

    .
    ├── build        # For building the project
    ├── cmake
    │   └── Modules  # Additional modules for CMake
    ├── cmd          # The command line client to tila
    │   ├── include  # Includes for the header files for the cmd
    │   └── src      # The source files
    ├── doc          # Manually written documentation (week reports etc)
    ├── example      # Examples of the tila language
    ├── lib          # Sourcecode for libtila, basically all of the actual code is here
    │   ├── include  # Headers and HeaderDoc documentation for the library
    │   └── src      # The source files
    └── test         # Folder for all of the tests
        ├── include  # Headers for the tests
        └── src      # Actual tests

Dependencies
------------

[CMake][cmake] for building. [Check][check] for testing. [LCOV][lcov] for test coverage. [HeaderDoc][hdoc] for documentation generation.

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


[course-link]: https://www.cs.helsinki.fi/courses/58161/2015/k/a/1
[travis-img]: https://img.shields.io/travis/JuhaniImberg/tila.svg?style=flat-square
[travis-link]: https://travis-ci.org/JuhaniImberg/tila
[coveralls-img]: https://img.shields.io/coveralls/JuhaniImberg/tila.svg?style=flat-square
[coveralls-link]: https://coveralls.io/r/JuhaniImberg/tila?branch=master
[docs-img]: https://img.shields.io/badge/docs-yep-brightgreen.svg?style=flat-square
[docs-link]: http://ahdoc.pieso.me/JuhaniImberg/tila/index.html
[cmake]: http://www.cmake.org/
[check]: http://check.sourceforge.net/
[lcov]: http://ltp.sourceforge.net/coverage/lcov.php
[hdoc]: https://developer.apple.com/library/mac/documentation/DeveloperTools/Conceptual/HeaderDoc/intro/intro.html
