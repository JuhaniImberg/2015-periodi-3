#include "tila.h"

struct Node *ArgumentNode_new(struct Vector *vector, struct Token *token,
                              struct GC *gc) {
    struct Node *node = Node_new(gc, token, N_ARGUMENT);
    node->vector = vector;
    node->repr = ArgumentNode_repr;
    return node;
}

void ArgumentNode_repr(struct Node *node, struct Environment *env) {
    ListNode_repr(node, env);
}
