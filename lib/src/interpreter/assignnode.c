#include "tila.h"

struct Node *AssignNode_new(struct Node *towhat, struct Token *token,
                            struct Node *what, struct GC *gc) {
    ASSERT(towhat->type != N_IDENTIFIER, "lvalue is not an identifier");
    struct Node *node = Node_new(gc, token, N_ASSIGN);
    node->repr = AssignNode_repr;
    node->get_value = AssignNode_get_value;
    node->left = towhat;
    node->right = what;
    return node;
}

void AssignNode_repr(struct Node *node, struct Environment *env) {
    InfixOperatorNode_repr(node, env);
}

void AssignNode_get_value(struct Node *node,
                                  struct Environment *env) {
    node->right->get_value(node->right, env);
    struct Node *val = GC_pop(node->gc);
    Environment_put(env,
                    Token_content(node->left->start, env->src),
                    val);
}
