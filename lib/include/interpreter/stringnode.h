#ifndef STRINGNODE_H
#define STRINGNODE_H

#include "tila.h"

/**
 * @brief Creates a new string node
 * @param token The token that holds the string inside
 */
struct Node *StringNode_new(struct Token *token, struct GC *gc);

/**
 * @brief Prints a representation of the string node
 */
void StringNode_repr(struct Node *, struct Environment *);

/**
 * @brief Pushes the string onto the return stack
 */
void StringNode_get_value(struct Node *node,
                          struct Environment *env);

#endif
