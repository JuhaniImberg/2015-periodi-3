#include "tila.h"

struct Node *Node_new(enum NodeTypeEnum type) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->type = type;
    return node;
}

void Node_delete(struct Node *node) {
    free(node);
}

struct Node *Node_identifier_new(struct Token *token) {
    ERROR(token->type->id != T_IDENTIFIER, "Token not an identifier");
    struct Node *node = Node_new(N_IDENTIFIER);
    node->start = token;
    return node;
}

char *Node_identifier_name(struct Node *node, struct Environment *env) {
    ERROR(node->type != N_IDENTIFIER, "Node not an identifier");
    return Token_content(node->start, env->src);
}

/*struct Node *Node_assign_new(struct Node *towhat, struct Node *what) {
    ERROR(towhat->type != N_IDENTIFIER, "lvalue is not an identifier");
    }*/
