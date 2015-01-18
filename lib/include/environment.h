#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "tila.h"
#include "node.h"

struct Environment {
    struct Map *nodes;
};

struct Environment *Environment_new();
void Environment_delete(struct Environment *environment);

#endif
