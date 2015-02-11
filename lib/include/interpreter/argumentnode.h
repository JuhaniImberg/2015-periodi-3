#ifndef ARGUMENTNODE_H
#define ARGUMENTNODE_H

#include "tila.h"

/**
 * @brief Creates a new argument node, for use with defining functions
 * @param vector Vector of the arguments that have been given
 * @param token The token that marks the start of this node
 */
struct  Node *ArgumentNode_new(struct Vector *vector, struct Token *token,
                               struct GC *gc);

void ArgumentNode_repr(struct Node *, struct Environment *);

#endif
