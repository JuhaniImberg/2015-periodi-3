#include "tila.h"

struct Node *NumberNode_new(struct Token *token, long long value,
                            struct GC *gc) {
    if(token != NULL) {
        ASSERT(token->type->id != T_NUMBER, "Token is not an number");
    }
    struct Node *node = Node_new(gc, token, N_NUMBER);
    node->repr = NumberNode_repr;
    node->get_value = NumberNode_get_value;
    node->data = malloc(sizeof(long long));
    memcpy(node->data, &value, sizeof(long long));
    return node;
}

void NumberNode_repr(struct Node *node,
                     struct Environment *env __attribute__((unused))) {
    printf("%lld", *(long long *)node->data);
}

void NumberNode_get_value(struct Node *node,
                          struct Environment *env __attribute__((unused))) {
    GC_push(node->gc, node);
}
