Specification document
======================

Problem to be solved
--------------------

A reasonably performing programming language interpreter, for a nice functional language.

Targets
-------

* Functional
* Light syntax
* Mostly immutable
* Macro system

Algorithms and data structures
------------------------------

| Data structure | For                         | Time Complexity | Space Complexity |
|----------------|-----------------------------|-----------------|------------------|
| Hash Table     | Scoping, use in programming | mostly `O(1)`   | `O(n)`           |
| Dynamic Array  | Use in programming          | mostly `O(n)`   | `O(n)`           |
| Stack          | Programs run on a stack     | `O(1)`          | `O(n)`           |

| Algorithm      | For                                 | Time Complexity | Space Complexity |
|----------------|-------------------------------------|-----------------|------------------|
| Pratt parser   | Creates an AST tree from the tokens | LL(1) `O(n)`    | `O(n)`           |
| Some tokenizer | Creates tokens from the source code | `O(n)`          | `O(n)`           |
| Some GC        | For collecting garbage              | Not sure        | Not sure         |
