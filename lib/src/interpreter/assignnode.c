#include "tila.h"

struct Node *AssignNode_new(struct Node *towhat, struct Token *token,
                            struct Node *what) {
    ASSERT(towhat->type != N_IDENTIFIER, "lvalue is not an identifier");
    struct Node *node = Node_new(N_ASSIGN);
    node->repr = AssignNode_repr;
    node->get_value = AssignNode_get_value;
    node->start = token;
    node->left = towhat;
    node->right = what;
    return node;
}

void AssignNode_repr(struct Node *node, struct Environment *env) {
    InfixOperatorNode_repr(node, env);
}

struct Node *AssignNode_get_value(struct Node *node,
                                  struct Environment *env) {
    struct Node *val = node->right->get_value(node->right, env);
    Environment_put(env,
                    Token_content(node->left->start, env->src),
                    val);
    return val;
}
