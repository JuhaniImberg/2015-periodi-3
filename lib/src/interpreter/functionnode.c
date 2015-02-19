#include "tila.h"

struct Node *FunctionNode_new(struct Vector *body, struct Node *args,
                              struct Token *token, struct GC *gc) {
    struct Node *node = Node_new(gc, token, N_FUNCTION);
    node->left = args;
    node->vector = body;
    node->repr = FunctionNode_repr;
    node->get_value = FunctionNode_get_value;
    return node;
}

void FunctionNode_repr(struct Node *node, struct Environment *env) {
    printf("(fn ");
    node->left->repr(node->left, env);
    printf(" ");
    ListNode_repr(node, env);
    printf(")");
}

void FunctionNode_call(struct Node *node,
                       struct Environment *env,
                       struct Vector *args_vals) {
    struct Environment *sub = Environment_new_sub(env);
    struct Vector *args_identifiers = node->left->vector;
    ASSERT(Vector_size(args_identifiers) != Vector_size(args_vals),
           "Function arguments length mismatch");
    FunctionNode_get_value(node, env);
    size_t len = Vector_size(args_vals);
    for(size_t i = 0; i < len; i++) {
        struct Node *identifier = Vector_get(args_identifiers, i);
        struct Node *val = Vector_get(args_vals, i);
        val->get_value(val, env);
        val = GC_pop(node->gc);
        Environment_put(sub,
                        Token_content(identifier->start, env->src),
                        val);
    }
    len = Vector_size(node->vector);
    struct Node *res = NULL;
    for(size_t i = 0; i < len; i++) {
        struct Node *nd = Vector_get(node->vector, i);
        if(nd != NULL) {
            nd->get_value(nd, sub);
            res = GC_pop(node->gc);
        }
    }
    Environment_delete(sub);
    GC_pop(node->gc);
    GC_push(node->gc, res);
}

void FunctionNode_get_value(struct Node *node,
                            struct Environment *env __attribute__((unused))) {
    GC_push(node->gc, node);
}
