Week 1 - Juhani Imberg
======================

What did I learn this week?
---------------------------

* How to use HeaderDoc for documentation
* How to use GitHubs webhooks for generating an event for my server to automatically generate the HeaderDoc HTML output
* How to use CTest and check for testing
* How to use gcov and lcov for testing line coverage
* How to use coveralls.io to track line coverage statistics

Unresolved things
-----------------

* How to have coveralls.io/lcov count the untested files towards the untested lines instead of ignoring them
* How to write clean object-oriented C with generics

How is the program progressing
------------------------------

* Implemented the vector and hashtable data structures
* Created a tokenizer (takes text and creates tokens out of it)
* Created the base parser (takes tokens and creates an abstract sytax tree from them)
* Tests and documentation for my own data structures

What will I do next
-------------------

* Create sub-parsers for each node type
* Create nodes (these hold the values and content in the environment)
* Create environment (the context in which the program is executed)
