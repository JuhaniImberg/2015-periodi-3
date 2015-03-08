Testing document
================

Unit tests
----------

    cd build
    ctest --output-on-failure

Only the data structures are tested, but they are tested pretty well.

Example programs
----------------

Being able to run the example programs with a output that looks valid is a good indicator that the program works.

There is no automated testing in place for these, since I tend to fiddle around them quite a bit.

To run one of the example programs

    ./build/cmd/tila examples/NAME.tila

It's usually helpful to see all of the information, so

    ./build/cmd/tila --returns --nodes --tokens examples/NAME.tile

will tell you most of the information about the different tokens, nodes and the return values.
