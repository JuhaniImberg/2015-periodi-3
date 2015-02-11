#include "tila.h"

struct Node *CallNode_new(struct Node *what, struct Token *token,
                          struct Vector *args, struct GC *gc) {
    struct Node *node = Node_new(gc, token, N_CALL);
    node->left = what;
    node->vector = args;
    node->repr = CallNode_repr;
    return node;
}

void CallNode_repr(struct Node *node, struct Environment *env) {
    printf("(");
    node->left->repr(node->left, env);
    printf(" ");
    ListNode_repr(node, env);
    printf(")");
}
