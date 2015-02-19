#ifndef LISTACCESSNODE_H
#define LISTACCESSNODE_H

#include "tila.h"

/**
 * @brief Creates a node that accesses the given list and returns the given
 *        index from the list
 * @param left The list that is being accessed
 * @param pos The position that will be accessed
 */
struct Node *ListAccessNode_new(struct Node *left, struct Token *token,
                                struct Node *pos, struct GC *gc);

/**
 * @brief Prints a representation of the list access
 */
void ListAccessNode_repr(struct Node *, struct Environment *);

/**
 * @brief Pushes the accessed value onto the return stack
 */
void ListAccessNode_get_value(struct Node *, struct Environment *);

#endif
