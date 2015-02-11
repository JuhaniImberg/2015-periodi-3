#ifndef LISTACCESSNODE_H
#define LISTACCESSNODE_H

#include "tila.h"

struct Node *ListAccessNode_new(struct Node *left, struct Token *token,
                                struct Node *pos);

void ListAccessNode_repr(struct Node *, struct Environment *);

#endif
