#ifndef GC_H
#define GC_H

#include "tila.h"

struct GC {
    struct Node *first_node;
    struct Environment *env;
    long long threshhold;
    long long max_threshhold;
};

struct GC *GC_new();
void GC_add(struct GC *gc, struct Node *node);
void GC_sweep(struct GC *gc);
void GC_delete(struct GC *gc);

#endif
