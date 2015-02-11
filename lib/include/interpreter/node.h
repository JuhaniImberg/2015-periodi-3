#ifndef NODE_H
#define NODE_H

#include "tila.h"
#include "environment.h"

/**
 * @brief The different types of nodes there are
 */
enum NodeTypeEnum {
    N_IDENTIFIER,
    N_NUMBER,
    N_FUNCTION,
    N_STRING,
    N_ASSIGN,
    N_CALL,
    N_ARGUMENT,
    N_LIST,
    N_INFIX_OPERATOR,
    N_LIST_ACCESS,
    N_CONDITIONAL
};

/**
 * @brief Holds every single kind of nodes there are
 * @field type The type of the node
 * @field start The starting token of the node
 * @field right If the node happens to be an infix operator this will be the
 *        lvalue
 * @field left If the node happens to be an infix operator this will be the
 *        rvalue
 * @field data Used to store arbitrary data in the node
 * @field get_value This method will be used for getting the nodes current value
 *                  in a given environment
 * @field marked Has the node been marked as safe from the GC for this round
 * @field next The next node that has been allocated
 */
struct Node {
    enum NodeTypeEnum type;
    struct Token *start;
    struct Node *left;
    struct Node *right;
    struct Vector *vector;
    void *data;
    struct Node *(*get_value)(struct Node *, struct Environment *environment);
    void (*repr)(struct Node *, struct Environment *environment);

    struct GC *gc;
    bool marked;
    struct Node *next;
};

/**
 * @brief Creates a new node
 * @param gc The garbage collector to be linked with
 * @param token The token where the node starts in the source, optional
 * @param type The type of the node
 */
struct Node *Node_new(struct GC *gc,
                      struct Token *start,
                      enum NodeTypeEnum type);

void Node_mark(struct Node *node);

void Node_mark_void_pointer(void *node);

/**
 * @brief Deletes a node
 */
void Node_delete(struct Node *node);

void Node_delete_void_pointer(void *data);

#include "argumentnode.h"
#include "assignnode.h"
#include "callnode.h"
#include "conditionalnode.h"
#include "functionnode.h"
#include "identifiernode.h"
#include "infixoperatornode.h"
#include "listaccessnode.h"
#include "listnode.h"
#include "numbernode.h"
#include "stringnode.h"

#endif
