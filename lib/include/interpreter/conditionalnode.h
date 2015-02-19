#ifndef CONDITIONALNODE_H
#define CONDITIONALNODE_H

#include "tila.h"

/**
 * @brief Creates a new conditional node
 * @param condition If this node evaluates to true this conditions body will be
 *                  evaluated
 * @param body The body of the conditional node, the things that get executed if
 *             the conditional is true
 */
struct Node *ConditionalNode_new(struct Node *condition, struct Token *token,
                                 struct Vector *body, struct GC *gc);

/**
 * @brief Prints a representation of the conditional
 */
void ConditionalNode_repr(struct Node *, struct Environment *);

/**
 * @brief Evaluates the nodes condition, if it is true then the nodes body will
 *        be evaluated also and the last thing returned to the return stack
 */
void ConditionalNode_get_value(struct Node *, struct Environment *);

#endif
