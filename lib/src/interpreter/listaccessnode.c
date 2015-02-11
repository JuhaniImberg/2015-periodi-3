#include "tila.h"

struct Node *ListAccessNode_new(struct Node *left, struct Token *token,
                                struct Node *pos, struct GC *gc) {
    struct Node *node = Node_new(gc, token, N_LIST_ACCESS);
    node->left = left;
    node->right = pos;
    node->repr = ListAccessNode_repr;
    return node;
}

void ListAccessNode_repr(struct Node *node, struct Environment *env) {
    node->left->repr(node->left, env);
    printf("[");
    node->right->repr(node->right, env);
    printf("]");
}
