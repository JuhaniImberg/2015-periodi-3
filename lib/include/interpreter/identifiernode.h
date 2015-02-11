#ifndef IDENTIFIERNODE_H
#define IDENTIFIERNODE_H

#include "tila.h"

/**
 * @brief Creates a new identifier node
 * @param token The token that is the actual identifier
 */
struct Node *IdentifierNode_new(struct Token *token, struct GC *gc);

char *IdentifierNode_name(struct Node *node, struct Environment *env);

void IdentifierNode_repr(struct Node *, struct Environment *);

struct Node *IdentifierNode_get_value(struct Node *, struct Environment *);


#endif
