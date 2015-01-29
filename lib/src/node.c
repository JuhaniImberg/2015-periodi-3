#include "tila.h"

struct Node *Node_new(enum NodeTypeEnum type) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    node->start = NULL;
    return node;
}

void Node_delete(struct Node *node) {
    free(node);
}

struct Node *Node_identifier_new(struct Token *token) {
    ASSERT(token->type->id != T_IDENTIFIER, "Token not an identifier");
    struct Node *node = Node_new(N_IDENTIFIER);
    node->start = token;
    return node;
}

char *Node_identifier_name(struct Node *node, struct Environment *env) {
    ASSERT(node->type != N_IDENTIFIER, "Node not an identifier");
    return Token_content(node->start, env->src);
}

struct Node *Node_assign_new(struct Node *towhat, struct Token *token,
                             struct Node *what) {
    ASSERT(towhat->type != N_IDENTIFIER, "lvalue is not an identifier");
    struct Node *node = Node_new(N_ASSIGN);
    node->start = token;
    node->left = towhat;
    node->right = what;
    return node;
}

struct Node *Node_number_new(struct Token *token) {
    ASSERT(token->type->id != T_NUMBER, "Token is not an number");
    struct Node *node = Node_new(N_NUMBER);
    node->start = token;
    return node;
}
