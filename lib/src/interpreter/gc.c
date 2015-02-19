#include "tila.h"

struct GC *GC_new() {
    struct GC *gc = malloc(sizeof(struct GC));
    gc->enabled = true;
    gc->stack = Vector_new();
    gc->first_node = NULL;
    gc->max_threshhold = 50;
    gc->threshhold = gc->max_threshhold;
    gc->env = NULL;
    return gc;
}

void GC_push(struct GC *gc, struct Node *node) {
    Vector_push(gc->stack, node);
}

struct Node *GC_pop(struct GC *gc) {
    return Vector_pop(gc->stack);
}

void GC_add(struct GC *gc, struct Node *node) {
    if(gc->threshhold <= 0 && gc->enabled) {
        if(gc->env != NULL) {
            Environment_mark(gc->env);
            Vector_each(gc->stack, Node_mark_void_pointer);
            GC_sweep(gc);
        }
        gc->threshhold = gc->max_threshhold;
    }

    node->gc = gc;
    node->marked = false;
    node->immortal = !gc->enabled;
    node->next = gc->first_node;
    gc->first_node = node;
    gc->threshhold--;
}

void GC_sweep(struct GC *gc) {
    DEBUG("GC Sweep");
    struct Node *node = gc->first_node;
    while(node != NULL) {
        if(node->marked || node->immortal) {
            node->marked = false;
            node = node->next;
        } else {
            DEBUG("GC Sweep killing %p %p", node, node->next);
            struct Node *kill = node;
            node = node->next;
            Node_delete(kill);
        }
    }
    gc->threshhold = gc->max_threshhold;
    DEBUG("GC Sweep over");
}

void GC_delete(struct GC *gc) {
    GC_sweep(gc);
    Vector_delete(gc->stack);
    free(gc);
}
