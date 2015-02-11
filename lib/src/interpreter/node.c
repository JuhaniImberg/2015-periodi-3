#include "tila.h"

struct Node *Node_new(struct GC *gc,
                      struct Token *start,
                      enum NodeTypeEnum type) {
    struct Node *node = malloc(sizeof(struct Node));
    node->type = type;
    node->vector = NULL;
    node->left = NULL;
    node->right = NULL;
    node->start = start;
    node->repr = NULL;
    node->data = NULL;

    GC_add(gc, node);

    return node;
}

void Node_mark(struct Node *node) {
    if(node->marked) {
        return;
    }
    node->marked = true;
    if(node->right != NULL) {
        Node_mark(node->right);
    }
    if(node->left != NULL) {
        Node_mark(node->left);
    }
    if(node->vector != NULL) {
        Vector_each(node->vector, Node_mark_void_pointer);
    }
}

void Node_mark_void_pointer(void *node) {
    Node_mark(node);
}

void Node_delete(struct Node *node) {
    if(node->vector != NULL) {
        Vector_each(node->vector, Node_delete_void_pointer);
        Vector_delete(node->vector);
    }
    if(node->data != NULL) {
        free(node->data);
    }
    free(node);
}

void Node_delete_void_pointer(void *data) {
    Node_delete(data);
}
