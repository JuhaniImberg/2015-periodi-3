#include "tila.h"

struct Node *Node_new(enum NodeTypeEnum type) {
    struct Node *node = malloc(sizeof(struct Node));
    node->type = type;
    node->vector = NULL;
    node->left = NULL;
    node->right = NULL;
    node->start = NULL;
    node->repr = NULL;
    return node;
}

void Node_delete_void_pointer(void *data) {
    Node_delete(data);
}

void Node_delete(struct Node *node) {
    if(node->vector != NULL) {
        Vector_each(node->vector, Node_delete_void_pointer);
        Vector_delete(node->vector);
    }
    if(node->right != NULL) {
        Node_delete(node->right);
    }
    if(node->left != NULL) {
        Node_delete(node->left);
    }
    free(node);
}

struct Node *IdentifierNode_new(struct Token *token) {
    ASSERT(token->type->id != T_IDENTIFIER, "Token not an identifier");
    struct Node *node = Node_new(N_IDENTIFIER);
    node->repr = IdentifierNode_repr;
    node->start = token;
    return node;
}

char *IdentifierNode_name(struct Node *node, struct Environment *env) {
    ASSERT(node->type != N_IDENTIFIER, "Node not an identifier");
    return Token_content(node->start, env->src);
}

struct Node *AssignNode_new(struct Node *towhat, struct Token *token,
                             struct Node *what) {
    ASSERT(towhat->type != N_IDENTIFIER, "lvalue is not an identifier");
    struct Node *node = Node_new(N_ASSIGN);
    node->repr = AssignNode_repr;
    node->start = token;
    node->left = towhat;
    node->right = what;
    return node;
}

struct Node *NumberNode_new(struct Token *token) {
    ASSERT(token->type->id != T_NUMBER, "Token is not an number");
    struct Node *node = Node_new(N_NUMBER);
    node->repr = NumberNode_repr;
    node->start = token;
    return node;
}

struct Node *StringNode_new(struct Token *token) {
    ASSERT(token->type->id != T_STRING, "Token is not a string");
    struct Node *node = Node_new(N_STRING);
    node->repr = StringNode_repr;
    node->start = token;
    return node;
}

struct Node *ArgumentNode_new(struct Vector *vector, struct Token *token) {
    struct Node *node = Node_new(N_ARGUMENT);
    node->start = token;
    node->vector = vector;
    node->repr = ArgumentNode_repr;
    return node;
}

struct Node *FunctionNode_new(struct Vector *body, struct Node *args,
                              struct Token *token) {
    struct Node *node = Node_new(N_FUNCTION);
    node->left = args;
    node->vector = body;
    node->start = token;
    node->repr = FunctionNode_repr;
    return node;
}

struct Node *CallNode_new(struct Node *what, struct Token *token,
                          struct Vector *args) {
    struct Node *node = Node_new(N_CALL);
    node->left = what;
    node->vector = args;
    node->start = token;
    node->repr = CallNode_repr;
    return node;
}

void IdentifierNode_repr(struct Node *node, struct Environment *env) {
    char *content = Token_content(node->start, env->src);
    printf("%s", content);
}

void AssignNode_repr(struct Node *node, struct Environment *env) {
    printf("(");
    node->left->repr(node->left, env);
    printf(" = ");
    node->right->repr(node->right, env);
    printf(")");
}

void NumberNode_repr(struct Node *node, struct Environment *env) {
    char *content = Token_content(node->start, env->src);
    printf("%s", content);
}

void StringNode_repr(struct Node *node, struct Environment *env) {
    char *content = Token_content(node->start, env->src);
    printf("%s", content);
}

void ArgumentNode_repr(struct Node *node, struct Environment *env) {
    size_t i, len = Vector_size(node->vector);
    printf("[");
    for(i = 0; i < len; i++) {
        struct Node *nd = Vector_get(node->vector, i);
        nd->repr(nd, env);
        if(i + 1 < len) {
            printf(", ");
        }
    }
    printf("]");
}

void FunctionNode_repr(struct Node *node, struct Environment *env) {
    printf("(fn ");
    node->left->repr(node->left, env);
    printf(" [");
    size_t i, len = Vector_size(node->vector);
    for(i = 0; i < len; i++) {
        struct Node *nd = Vector_get(node->vector, i);
        nd->repr(nd, env);
        if(i + 1 < len) {
            printf(", ");
        }
    }
    printf("])");
}

void CallNode_repr(struct Node *node, struct Environment *env) {
    printf("(");
    node->left->repr(node->left, env);
    printf(" [");
    size_t i, len = Vector_size(node->vector);
    for(i = 0; i < len; i++) {
        struct Node *nd = Vector_get(node->vector, i);
        nd->repr(nd, env);
        if(i + 1 < len) {
            printf(", ");
        }
    }
    printf(")");
}
