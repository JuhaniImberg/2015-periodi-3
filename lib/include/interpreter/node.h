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
};

/**
 * @brief Holds every single kind of nodes there are
 * @field type The type of the node
 * @field start The starting token of the node
 * @field right If the node happens to be an infix operator this will be the
 *        lvalue
 * @field left If the node happens to be an infix operator this will be the
 *        rvalue
 * @field get_value This method will be used for getting the nodes current value
 *                  in a given environment
 */
struct Node {
    enum NodeTypeEnum type;
    struct Token *start;
    struct Node *left;
    struct Node *right;
    struct Vector *vector;
    struct Node *(*get_value)(struct Node *, struct Environment *environment);
    void (*repr)(struct Node *, struct Environment *environment);
};

/**
 * @brief Creates a new node
 * @param type The type of the node
 */
struct Node *Node_new(enum NodeTypeEnum type);

/**
 * @brief Deletes a node
 */
void Node_delete(struct Node *node);

/**
 * @brief Creates a new identifier node
 * @param token The token that is the actual identifier
 */
struct Node *IdentifierNode_new(struct Token *token);
char *IdentifierNode_name(struct Node *node, struct Environment *env);

/**
 * @brief Creates a new assignment node (a = b)
 * @param towhat To what is what assigned
 * @param what What is assigned to towhat
 * @token The assignment operators token, just for completeness
 */
struct Node *AssignNode_new(struct Node *towhat, struct Token *token,
                            struct Node *what);

/**
 * @brief Creates a new number node
 */
struct Node *NumberNode_new(struct Token *token);

struct Node *StringNode_new(struct Token *token);

struct  Node *ArgumentNode_new(struct Vector *vector, struct Token *token);

struct Node *FunctionNode_new(struct Vector *body, struct Node *args,
                              struct Token *token);

struct Node *CallNode_new(struct Node *what, struct Token *token,
                          struct Vector *args);

void IdentifierNode_repr(struct Node *, struct Environment *);
void AssignNode_repr(struct Node *, struct Environment *);
void NumberNode_repr(struct Node *, struct Environment *);
void StringNode_repr(struct Node *, struct Environment *);
void ArgumentNode_repr(struct Node *, struct Environment *);
void FunctionNode_repr(struct Node *, struct Environment *);
void CallNode_repr(struct Node *, struct Environment *);


#endif
