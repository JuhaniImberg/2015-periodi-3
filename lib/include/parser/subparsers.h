#ifndef SUBPARSERS_H
#define SUBPARSERS_H

#include "tila.h"

struct Node *identifier_parser(struct Parser *parser,
                               struct Token *token);

struct Node *assign_parser(struct Parser *parser,
                           struct Node *left,
                           struct Token *token);

struct Node *number_parser(struct Parser *parser,
                           struct Token *token);

#endif
