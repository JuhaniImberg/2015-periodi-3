#ifndef CONDITIONALNODE_H
#define CONDITIONALNODE_H

#include "tila.h"

struct Node *ConditionalNode_new(struct Node *condition, struct Token *token,
                                 struct Vector *body, struct GC *gc);


void ConditionalNode_repr(struct Node *, struct Environment *);

struct Node *ConditionalNode_get_value(struct Node *, struct Environment *);

#endif
