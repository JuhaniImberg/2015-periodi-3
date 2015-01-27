#ifndef NODE_H
#define NODE_H

#include "tila.h"
#include "environment.h"

enum NodeTypeEnum {
    N_IDENTIFIER,
    N_NUMBER,
    N_FN,
    N_STRING,
    N_SET,
    N_CALL
};

struct Node {
    enum NodeTypeEnum type;
    struct Token *start;
    struct Node *(*get_value)(struct Environment *environment);
};

struct Node *Node_new(enum NodeTypeEnum type);
void Node_delete(struct Node *node);

struct Node *Node_identifier_new(struct Token *token);
char *Node_identifier_name(struct Node *node, struct Environment *env);

#endif
