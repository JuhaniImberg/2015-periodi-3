#ifndef VECTOR_H
#define VECTOR_H

#include "tila.h"

struct Vector {
    unsigned int size;
    unsigned int allocated_size;
    void **data;
};

struct Vector *Vector_new();
unsigned int Vector_size(struct Vector *vector);
bool Vector_empty(struct Vector *vector);
void Vector_clear(struct Vector *vector);
void Vector_set(struct Vector *vector, unsigned int pos, void *data);
void Vector_insert(struct Vector *vector, unsigned int pos, void *data);
void *Vector_get(struct Vector *vector, unsigned int pos);
void *Vector_remove(struct Vector *vector, unsigned int pos);
void Vector_add(struct Vector *vector, void *data);
void Vector_push(struct Vector *vector, void *data);
void *Vector_pop(struct Vector *vector);
void *Vector_top(struct Vector *vector);

void Vector_delete(struct Vector *vector);

#endif
