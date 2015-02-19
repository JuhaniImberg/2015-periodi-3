#ifndef IDENTIFIERNODE_H
#define IDENTIFIERNODE_H

#include "tila.h"

/**
 * @brief Creates a new identifier node, a node that holds a string as its name
 *        and enables storing things under that identifier in a environment
 * @param token The token that is the actual identifier
 */
struct Node *IdentifierNode_new(struct Token *token, struct GC *gc);

/**
 * @brief Returns the name of the identifier
 * @returns The name of the identifier
 */
char *IdentifierNode_name(struct Node *node, struct Environment *env);

/**
 * @brief Prints a representation of the identifier
 */
void IdentifierNode_repr(struct Node *, struct Environment *);

/**
 * @brief Pushes the value that is associated with the identifier in the
 *        environment to the return stack
 */
void IdentifierNode_get_value(struct Node *, struct Environment *);


#endif
