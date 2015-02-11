#include "tila.h"

struct Node *FunctionNode_new(struct Vector *body, struct Node *args,
                              struct Token *token, struct GC *gc) {
    struct Node *node = Node_new(gc, token, N_FUNCTION);
    node->left = args;
    node->vector = body;
    node->repr = FunctionNode_repr;
    return node;
}

void FunctionNode_repr(struct Node *node, struct Environment *env) {
    printf("(fn ");
    node->left->repr(node->left, env);
    printf(" ");
    ListNode_repr(node, env);
    printf(")");
}

struct Node *FunctionNode_call(struct Node *node,
                               struct Environment *env,
                               struct Vector *args_vals) {
    struct Environment *sub = Environment_new_sub(env);
    struct Vector *args_identifiers = node->left->vector;
    ASSERT(Vector_size(args_identifiers) != Vector_size(args_vals),
           "Function arguments length mismatch");
    size_t len = Vector_size(args_vals);
    for(size_t i = 0; i < len; i++) {
        struct Node *identifier = Vector_get(args_identifiers, i);
        struct Node *val = Vector_get(args_vals, i);
        Environment_put(sub,
                        Token_content(identifier->start, env->src),
                        val);
    }
    len = Vector_size(node->vector);
    for(size_t i = 0; i < len; i++) {
        struct Node *nd = Vector_get(node->vector, i);
        if(nd != NULL) {
            nd->get_value(nd, sub);
        }
    }
    Environment_delete(sub);
    return NULL;
}

struct Node *FunctionNode_get_value(struct Node *node,
                                    struct Environment *env __attribute__((unused))) {
    return node;
}
