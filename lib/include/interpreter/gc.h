#ifndef GC_H
#define GC_H

#include "tila.h"

/**
 * @brief Describes the languages Garbage Collector
 * @field enabled Is the garbage collector enabled
 * @field stack The return stack of the program
 * @field first_node Keeps track of the added nodes
 * @field env The environment the program is currently operating in
 * @field threshhold Keeps track of how many allocations can happen before the
 *                   GC tries to free some memory
 * @field max_threshhold How many allocations can happen before the GC tries to
 *                       free some memory
 */
struct GC {
    bool enabled;
    struct Vector *stack;
    struct Node *first_node;
    struct Environment *env;
    long long threshhold;
    long long max_threshhold;
};

/**
 * @brief Creates a new garbage collector
 */
struct GC *GC_new();

/**
 * @brief Pushes a node to the result stack
 */
void GC_push(struct GC *gc, struct Node *node);

/**
 * @brief Pops a result from the result stack
 */
struct Node *GC_pop(struct GC *gc);

/**
 * @brief Adds the node to the garbage collector tracking
 */
void GC_add(struct GC *gc, struct Node *node);

/**
 * @brief Tries to free some memory by sweeping through all of the allocated
 *        nodes and sees if some nodes haven't been reached in the marking
 *        phase
 */
void GC_sweep(struct GC *gc);

/**
 * @brief Deletes the garbage collector
 */
void GC_delete(struct GC *gc);

#endif
