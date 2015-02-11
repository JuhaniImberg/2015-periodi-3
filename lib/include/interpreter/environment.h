#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "tila.h"
#include "node.h"

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
};

/**
 * @brief Creates a new environment
 * @field src The source code of the environment, for nodes to refer to
 */
struct Environment *Environment_new(char *src);

struct Environment *Environment_new_sub(struct Environment *env);

struct Node *Environment_get(struct Environment *env,
                             char *key);

void Environment_put(struct Environment *env,
                     char *key,
                     struct Node *value);

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
