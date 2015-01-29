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
    N_FN,
    N_STRING,
    N_ASSIGN,
    N_CALL
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
    struct Node *(*get_value)(struct Environment *environment);
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
struct Node *Node_identifier_new(struct Token *token);
char *Node_identifier_name(struct Node *node, struct Environment *env);

/**
 * @brief Creates a new assignment node
 * @param towhat To what is what assigned
 * @param what What is assigned to towhat
 * @token The assignment operators token, just for completeness
 */
struct Node *Node_assign_new(struct Node *towhat, struct Token *token,
                             struct Node *what);

/**
 * @brief Creates a new number node
 */
struct Node *Node_number_new(struct Token *token);

#endif
