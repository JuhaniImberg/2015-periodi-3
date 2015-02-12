#include "tila.h"

struct GC *GC_new() {
    struct GC *gc = malloc(sizeof(struct GC));
    gc->first_node = NULL;
    gc->max_threshhold = 100;
    gc->threshhold = gc->max_threshhold;
    gc->env = NULL;
    return gc;
}

void GC_add(struct GC *gc, struct Node *node) {
    if(gc->threshhold <= 0) {
        if(gc->env != NULL) {
            Environment_mark(gc->env);
            GC_sweep(gc);
        }
        gc->threshhold = gc->max_threshhold;
    }

    node->gc = gc;
    node->marked = false;
    node->next = gc->first_node;
    gc->first_node = node;
    gc->threshhold--;
}

void GC_sweep(struct GC *gc) {
    DEBUG("GC Sweep");
    struct Node *node = gc->first_node;
    while(node != NULL) {
        if(node->marked) {
            node->marked = false;
            node = node->next;
        } else {
            struct Node *kill = node;
            node = node->next;
            Node_delete(kill);
        }
    }
    gc->threshhold = gc->max_threshhold;
}

void GC_delete(struct GC *gc) {
    GC_sweep(gc);
    free(gc);
}
