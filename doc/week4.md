Week 4 - Juhani Imberg
======================

What did I learn this week?
---------------------------

* How garbage collectors work
* I have a few big design flaws in my design

Unresolved things
-----------------

* How to magically make more time for everything
* How to not catch a virus
  * Easier on computers
  * Humans still a mystery

How is the program progressing
------------------------------

* It can run simple programs made out of variables, numbers and operators. See `examples/math.tila`
* You can define functions and call them
* Conditionals work somewhat
* There is a very basic mark and sweep garbage collection algorithm
* I didn't have much time to write tests and documentation

What will I do next
-------------------

* Start using my own stack, instead of relaying on the underlying systems stack. This is because currently the GC will free stuff that are actually in use, but they haven't been added to any node or to the environment hash table. This means things that are currently being calculated can disappear
* Think about a macro system for looping and such
* Tests for parser and nodes
* Documentation for nodes
