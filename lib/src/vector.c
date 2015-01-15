#include "tila.h"

struct Vector *Vector_new() {
    struct Vector *vector = (struct Vector *)malloc(sizeof(struct Vector));
    vector->size = 0;
    vector->allocated_size = 10;
    vector->data = malloc(vector->allocated_size * sizeof(void *));
    return vector;
}

void Vector_resize(struct Vector *vector, unsigned int newsize) {
    vector->data = realloc(vector->data, newsize * sizeof(void *));
    vector->allocated_size = newsize;
}

unsigned int Vector_size(struct Vector *vector) {
    return vector->size;
}

void Vector_add(struct Vector *vector, void *data) {
    if(vector->size == vector->allocated_size - 2) {
        Vector_resize(vector, vector->allocated_size * 2);
    }
    vector->data[vector->size++] = data;
}

void Vector_set(struct Vector *vector, unsigned int pos, void *data) {
    if(vector->size <= pos) {
        return;
    }
    vector->data[pos] = data;
}

void *Vector_get(struct Vector *vector, unsigned int pos) {
    if(vector->size <= pos) {
        return NULL;
    }
    return vector->data[pos];
}

void *Vector_remove(struct Vector *vector, unsigned int pos) {
    if(vector->size <= pos) {
        return NULL;
    }
    void *data = vector->data[pos];
    memmove(&vector->data[pos], &vector->data[pos] + 1, (vector->size - pos) * sizeof(void *) );
    vector->size--;
    return data;
}

void Vector_delete(struct Vector *vector) {
    free(vector->data);
    free(vector);
}
