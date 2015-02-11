#ifndef FUNCTIONNODE_H
#define FUNCTIONNODE_H

#include "tila.h"

/**
 * @brief Creates a new function node, represents a function
 * @param body A vector of the nodes that are under this one
 * @param args An ArgumentNode that has the arguments that are passed to this
 *             function when called
 * @param token The token that marks the start of this node
 */
struct Node *FunctionNode_new(struct Vector *body, struct Node *args,
                              struct Token *token, struct GC *gc);

void FunctionNode_repr(struct Node *, struct Environment *);

struct Node *FunctioNode_call(struct Node *, struct Environment *,
                              struct Vector *);

struct Node *FunctionNode_get_value(struct Node *, struct Environment *);

#endif
