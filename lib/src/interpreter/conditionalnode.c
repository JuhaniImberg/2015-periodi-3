#include "tila.h"

struct Node *ConditionalNode_new(struct Node *condition, struct Token *token,
                                 struct Vector *body, struct GC *gc) {
    struct Node *node = Node_new(gc, token, N_CONDITIONAL);
    node->repr = ConditionalNode_repr;
    node->get_value = ConditionalNode_get_value;
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

struct Node *ConditionalNode_get_value(struct Node *node,
                                       struct Environment *env) {
    struct Node *cond = node->left->get_value(node->left, env);
    if(cond == NULL) return NULL;
    ASSERT(cond->type != N_NUMBER, "Condition result not a integer/boolean");
    long long val = *(long long *)cond->data;
    if(val == 1) {
        struct Node *res = NULL;
        struct Environment *sub = Environment_new_sub(env);
        for(size_t i = 0; i < node->vector->size; i++) {
            struct Node *nd = Vector_get(node->vector, i);
            res = nd->get_value(nd, sub);
        }
        Environment_delete(sub);
        return res;
    } else {
        return NULL;
    }
}
