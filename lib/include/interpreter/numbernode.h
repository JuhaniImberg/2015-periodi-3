#ifndef NUMBERNODE_H
#define NUMBERNODE_H

#include "tila.h"

/**
 * @brief Creates a new number node
 * @param token The token that holds the number inside, optional
 * @param value The value of the number
 */
struct Node *NumberNode_new(struct Token *token, long long value,
                            struct GC *gc);

void NumberNode_repr(struct Node *, struct Environment *);

struct Node *NumberNode_get_value(struct Node *, struct Environment *);


#endif
