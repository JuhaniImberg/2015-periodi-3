Usage document
==============

Compiling
---------

    cd build
    cmake ..
    make

Running
-------

    ./build/cmd/tila FILE

Example files are in `examples`

Language specification
----------------------

Comments

    # I'm a comment

Assigning a thing

    a = 3

Getting a thing

    a   # 3

Math

    3 + 2  # 5
    6 / 3  # 2
    2 - 3  # -1
    2 * 8  # 16
    7 % 5  # 2

Lists

    b = [3, 2, 1, 0]

Getting a thing from a list

    b[1]  # 2

Appending or prepending to a list

    b + [-1]   # [3, 2, 1, 0, -1]

Conditionals

    a == 3 ?
      # a is 3
    !?
      # a is not 3

Comparing operators

    == >= <= < > !=

Joining operators

    && ||

Functions

    (argument1, argument2) ->
      argument1 + argument2

Printing something

    "Value of a: {a}"  # Value of a: 3

Recursion

    rec = (i, n) ->
      "Step {i} of {n}"
      i != n ?
        rec(i + 1, n)

    rec(0, 10)
