#include "tila.h"

struct Node *StringNode_new(struct Token *token) {
    ASSERT(token->type->id != T_STRING, "Token is not a string");
    struct Node *node = Node_new(N_STRING);
    node->repr = StringNode_repr;
    node->start = token;
    return node;
}

void StringNode_repr(struct Node *node, struct Environment *env) {
    char *content = Token_content(node->start, env->src);
    printf("%s", content);
}

struct Node *StringNode_get_value(struct Node *node,
                                  struct Environment *env __attribute__((unused))) {
    return node;
}
