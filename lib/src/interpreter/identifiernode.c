#include "tila.h"

struct Node *IdentifierNode_new(struct Token *token, struct GC *gc) {
    ASSERT(token->type->id != T_IDENTIFIER, "Token not an identifier");
    struct Node *node = Node_new(gc, token, N_IDENTIFIER);
    node->repr = IdentifierNode_repr;
    node->get_value = IdentifierNode_get_value;
    return node;
}

char *IdentifierNode_name(struct Node *node, struct Environment *env) {
    ASSERT(node->type != N_IDENTIFIER, "Node not an identifier");
    return Token_content(node->start, env->src);
}

void IdentifierNode_repr(struct Node *node, struct Environment *env) {
    char *content = Token_content(node->start, env->src);
    printf("%s", content);
}

struct Node *IdentifierNode_get_value(struct Node *node,
                                      struct Environment *env) {
    return Environment_get(env, Token_content(node->start, env->src));
}
