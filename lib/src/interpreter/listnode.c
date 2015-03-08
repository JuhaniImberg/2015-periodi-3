#include "tila.h"

struct Node *ListNode_new(struct Vector *nodes, struct Token *token,
                          struct GC *gc) {
    struct Node *node = Node_new(gc, token, N_LIST);
    node->vector = nodes;
    node->repr = ListNode_repr;
    node->get_value = ListNode_get_value;
    return node;
}

void ListNode_repr(struct Node *node, struct Environment *env) {
    printf("[");
    size_t i, len = Vector_size(node->vector);
    for(i = 0; i < len; i++) {
        struct Node *nd = Vector_get(node->vector, i);
        nd->repr(nd, env);
        if(i + 1 < len) {
            printf(", ");
        }
    }
    printf("]");
}

void ListNode_get_value(struct Node *node,
                        struct Environment *env) {
    struct Vector *new = Vector_new();
    for(size_t i = 0; i < node->vector->size; i++) {
        struct Node *sub = Vector_get(node->vector, i);
        sub->get_value(sub, env);
        sub = GC_pop(node->gc);
        Vector_push(new, sub);
    }
    struct Node *result = ListNode_new(new, node->start, node->gc);
    GC_push(node->gc, result);
}
