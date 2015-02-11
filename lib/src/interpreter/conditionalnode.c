#include "tila.h"

struct Node *ConditionalNode_new(struct Node *condition, struct Token *token,
                                 struct Vector *body, struct GC *gc) {
    struct Node *node = Node_new(gc, token, N_CONDITIONAL);
    node->repr = ConditionalNode_repr;
    node->left = condition;
    node->vector = body;
    return node;
}

void ConditionalNode_repr(struct Node *node, struct Environment *env) {
    printf("(if ");
    node->left->repr(node->left, env);
    printf(" ");
    ListNode_repr(node, env);
    printf(")");
}
