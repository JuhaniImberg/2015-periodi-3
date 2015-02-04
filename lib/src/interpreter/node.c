#include "tila.h"

struct Node *Node_new(enum NodeTypeEnum type) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->type = type;
    node->vector = NULL;
    node->left = NULL;
    node->right = NULL;
    node->start = NULL;
    node->repr = NULL;
    return node;
}

void Node_delete(struct Node *node) {
    if(node->vector != NULL) {
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
