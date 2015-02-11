#ifndef ASSIGNNODE_H
#define ASSIGNNODE_H

#include "tila.h"

/**
 * @brief Creates a new assignment node (a = b)
 * @param towhat To what is what assigned
 * @param what What is assigned to towhat
 * @token The assignment operators token, just for completeness
 */
struct Node *AssignNode_new(struct Node *towhat, struct Token *token,
                            struct Node *what, struct GC *gc);

void AssignNode_repr(struct Node *, struct Environment *);

struct Node *AssignNode_get_value(struct Node *, struct Environment *);


#endif
