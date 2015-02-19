#include "tila.h"

struct Node *InfixOperatorNode_new(struct Node *left, struct Token *token,
                                   struct Node *right, struct GC *gc) {
    struct Node *node = Node_new(gc, token, N_INFIX_OPERATOR);
    node->left = left;
    node->right = right;
    node->get_value = InfixOperatorNode_get_value;
    node->repr = InfixOperatorNode_repr;
    return node;
}

void InfixOperatorNode_repr(struct Node *node, struct Environment *env) {
    printf("(");
    printf("%s ", Token_content(node->start, env->src));
    node->left->repr(node->left, env);
    printf(" ");
    node->right->repr(node->right, env);
    printf(")");
}

void InfixOperatorNode_get_value(struct Node *node,
                                 struct Environment *env) {
    node->left->get_value(node->left, env);
    struct Node *left = GC_pop(node->gc);
    node->right->get_value(node->right, env);
    struct Node *right = GC_pop(node->gc);
    if(left != NULL && right != NULL &&
       left->type == N_NUMBER && right->type == N_NUMBER) {
        long long lval = *(long long *)left->data;
        long long rval = *(long long *)right->data;
        long long nval = 0;
        switch(node->start->type->id) {
        case T_ADD:
            nval = lval + rval;
            break;
        case T_SUB:
            nval = lval - rval;
            break;
        case T_MUL:
            nval = lval * rval;
            break;
        case T_DIV:
            nval = lval / rval;
            break;
        case T_MOD:
            nval = lval % rval;
            break;
        case T_EQ:
            nval = (lval == rval);
            break;
        case T_NOTEQ:
            nval = (lval != rval);
            break;
        case T_LT:
            nval = (lval < rval);
            break;
        case T_LTOE:
            nval = (lval <= rval);
            break;
        case T_GT:
            nval = (lval > rval);
            break;
        case T_GTOE:
            nval = (lval >= rval);
            break;
        default: // This should never be reached
            ASSERT(1, "Unknown token type met in infix operator node");
        }
        GC_push(node->gc, NumberNode_new(NULL, nval, node->gc));
        return;
    }
    ASSERT(1, "Unknown data types for infix operator");
}
