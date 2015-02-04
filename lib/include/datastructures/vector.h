#ifndef VECTOR_H
#define VECTOR_H

#include "tila.h"

/**
 * @brief A vector is a dynamic sized array
 * @field size How many elements are in the vector
 * @field allocated_size How much memory is allocated for the vector
 * @field data Holds the allocated memory
 */
struct Vector {
    unsigned int size;
    unsigned int allocated_size;
    void **data;
};

/**
 * @brief Creates a new vector
 */
struct Vector *Vector_new();

/**
 * @brief How big the vector is
 * @returns How big the vector is
 */
unsigned int Vector_size(struct Vector *vector);

/**
 * @brief Is the vector empty
 * @returns True if the vector is empty
 */
bool Vector_empty(struct Vector *vector);

/**
 * @brief Resets the vectors state
 */
void Vector_clear(struct Vector *vector);

/**
 * @brief Sets an element in the vector to the given value
 * @param pos The position to be modified
 * @pparam data The value that will be assigned to the pos
 */
void Vector_set(struct Vector *vector, unsigned int pos, void *data);

/**
 * @brief Inserts an element in the vector
 * @param pos In which position should the data be inserted
 * @param data The data to be inserted
 */
void Vector_insert(struct Vector *vector, unsigned int pos, void *data);

/**
 * @brief Gets an element from the vector
 * @param pos The position to be retrieved
 * @returns The data in the position, if the position is out of bounds NULL
 */
void *Vector_get(struct Vector *vector, unsigned int pos);

/**
 * @brief Removes an element from the vector
 * @param pos The position of the element to be removed
 * @returns The data that was in the position, or NULL if out of bounds
 */
void *Vector_remove(struct Vector *vector, unsigned int pos);

/**
 * @brief Adds the data to the end of the vector
 * @param data The data to be added
 */
void Vector_add(struct Vector *vector, void *data);

/**
 * @brief Adds the data to the end of the vector
 * @param data The data to be added
 */
void Vector_push(struct Vector *vector, void *data);

/**
 * @brief Removes the last element in the vector and returns it
 * @returns The last element in the vector
 */
void *Vector_pop(struct Vector *vector);

/**
 * @brief Returns the last element in the vector
 * @returns The last element in the vector
 */
void *Vector_top(struct Vector *vector);

/**
 * @brief Calls cb on each of the elements that are not null
 * @param cb A function that gets called on each of the elements
 */
void Vector_each(struct Vector *vector, void (*cb)(void *));

/**
 * @brief Deallocates all of the memory that was assigned to the vector
 */
void Vector_delete(struct Vector *vector);

#endif
