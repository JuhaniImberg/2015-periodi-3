#include "tila.h"

struct Node *StringNode_new(struct Token *token, struct GC *gc) {
    ASSERT(token->type->id != T_STRING, "Token is not a string");
    struct Node *node = Node_new(gc, token, N_STRING);
    node->repr = StringNode_repr;
    return node;
}

void StringNode_repr(struct Node *node, struct Environment *env) {
    char *content = Token_content(node->start, env->src);
    printf("%s", content);
}

void StringNode_get_value(struct Node *node,
                          struct Environment *env __attribute__((unused))) {
    GC_push(node->gc, node);
}
