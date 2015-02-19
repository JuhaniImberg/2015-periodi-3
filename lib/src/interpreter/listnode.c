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
                        struct Environment *env __attribute__((unused))) {
    GC_push(node->gc, node);
}
