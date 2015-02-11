#ifndef LISTNODE_H
#define LISTNODE_H

#include "tila.h"

struct Node *ListNode_new(struct Vector *nodes, struct Token *token);

void ListNode_repr(struct Node *, struct Environment *);

struct Node *ListNode_get_value(struct Node *, struct Environment *);

#endif
