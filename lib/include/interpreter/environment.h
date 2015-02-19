#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "tila.h"
#include "node.h"
#include "gc.h"

/**
 * @brief Holds the status of the interpreter
 * @field symbols The symbols that are in the current scope, for example
 *                variable name is the key and value is the value
 * @field src The source code of this environment
 */
struct Environment {
    struct Environment *parent;
    struct Map *symbols;
    char *src;
    struct GC *gc;
};

/**
 * @brief Creates a new environment
 * @field src The source code of the environment, for nodes to refer to
 */
struct Environment *Environment_new(struct GC *gc, char *src);

/**
 * @brief Creates a new child environment, for limiting the leakage of variable
 *        names to a outer scope
 */
struct Environment *Environment_new_sub(struct Environment *env);

/**
 * @brief Marks all of the reachable nodes as safe from the next GC sweep
 */
void Environment_mark(struct Environment *env);

/**
 * @brief Returns the node that is associated with the key. Checks the
 *        environments parents recursively.
 * @param key The key that gets checked for
 * @returns The found node or NULL
 */
struct Node *Environment_get(struct Environment *env,
                             char *key);

/**
 * @brief Associates a value with the key
 */
void Environment_put(struct Environment *env,
                     char *key,
                     struct Node *value);

/**
 * @brief Does the environment contain the given key
 */
bool Environment_contains(struct Environment *env,
                          char *key);

/**
 * @brief Evaluates the node in this environment
 */
struct Node *Environment_evaluate_node(struct Environment *env,
                                       struct Node *node);

/**
 * @brief Deletes the environment
 */
void Environment_delete(struct Environment *environment);

#endif
