#ifndef INFIXOPERATORNODE_H
#define INFIXOPERATORNODE_H

#include "tila.h"

/**
 * @brief Creates a new infix operation node, a node that represents the
 *        operation between two other nodes (like addition)
 * @param left The left node
 * @param right The right node
 * @param token The token that represents the operation
 */
struct Node *InfixOperatorNode_new(struct Node *left, struct Token *token,
                                   struct Node *right, struct GC *gc);

/**
 * @brief Prints the representation of the infix operator
 */
void InfixOperatorNode_repr(struct Node *, struct Environment *);

/**
 * @brief Makes the calculation between the two nodes and pushes the result
 *        to the return stack
 */
void InfixOperatorNode_get_value(struct Node *, struct Environment *);


#endif
