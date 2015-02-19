#include "tila.h"

struct Node *ListAccessNode_new(struct Node *left, struct Token *token,
                                struct Node *pos, struct GC *gc) {
    struct Node *node = Node_new(gc, token, N_LIST_ACCESS);
    node->left = left;
    node->right = pos;
    node->repr = ListAccessNode_repr;
    node->get_value = ListAccessNode_get_value;
    return node;
}

void ListAccessNode_repr(struct Node *node, struct Environment *env) {
    node->left->repr(node->left, env);
    printf("[");
    node->right->repr(node->right, env);
    printf("]");
}

void ListAccessNode_get_value(struct Node *node, struct Environment *env) {
    node->left->get_value(node->left, env);
    struct Node *list = GC_pop(node->gc);
    node->right->get_value(node->right, env);
    struct Node *pos = GC_pop(node->gc);
    ASSERT(list->type != N_LIST, "Trying to access a node that isn't a list");
    ASSERT(pos->type != N_NUMBER, "Trying to access a list with a index that's not a number");
    GC_push(node->gc, Vector_get(list->vector, *(long long *)pos->data));
}
