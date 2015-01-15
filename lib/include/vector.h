#ifndef VECTOR_H
#define VECTOR_H

struct Vector {
    unsigned int size;
    unsigned int allocated_size;
    void **data;
};

struct Vector *Vector_new();
unsigned int Vector_size(struct Vector *vector);
void Vector_set(struct Vector *vector, unsigned int pos, void *data);
void *Vector_get(struct Vector *vector, unsigned int pos);
void *Vector_remove(struct Vector *vector, unsigned int pos);
void Vector_add(struct Vector *vector, void *data);
void Vector_delete(struct Vector *vector);

#endif
