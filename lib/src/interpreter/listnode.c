#include "tila.h"

struct Node *ListNode_new(struct Vector *nodes, struct Token *token) {
    struct Node *node = Node_new(N_LIST);
    node->vector = nodes;
    node->start = token;
    node->repr = ListNode_repr;
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

struct Node *ListNode_get_value(struct Node *node,
                                struct Environment *env __attribute__((unused))) {
    return node;
}
