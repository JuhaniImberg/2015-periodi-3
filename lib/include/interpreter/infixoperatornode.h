#ifndef INFIXOPERATORNODE_H
#define INFIXOPERATORNODE_H

#include "tila.h"

struct Node *InfixOperatorNode_new(struct Node *left, struct Token *token,
                                   struct Node *right, struct GC *gc);

void InfixOperatorNode_repr(struct Node *, struct Environment *);

struct Node *InfixOperatorNode_get_value(struct Node *, struct Environment *);


#endif
