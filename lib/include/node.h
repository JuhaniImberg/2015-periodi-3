#ifndef NODE_H
#define NODE_H

#include "tila.h"
#include "environment.h"

struct Node {
    struct Node *(*value)(struct Environment *environment);
};

#endif
