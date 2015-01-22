#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "tila.h"
#include "node.h"

/**
 * @brief Holds the status of the interpreter
 * @field nodes The nodes that are in the current scope
 */
struct Environment {
    struct Map *nodes;
};

struct Environment *Environment_new();
void Environment_delete(struct Environment *environment);

#endif