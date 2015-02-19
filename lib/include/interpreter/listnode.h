#ifndef LISTNODE_H
#define LISTNODE_H

#include "tila.h"

/**
 * @brief Creates a new list node
 * @brief nodes The contained nodes
 */
struct Node *ListNode_new(struct Vector *nodes, struct Token *token,
                          struct GC *gc);

/**
 * @brief Prints a representation of the list
 */
void ListNode_repr(struct Node *, struct Environment *);

/**
 * @brief Pushes the list onto the return stack
 */
void ListNode_get_value(struct Node *, struct Environment *);

#endif
