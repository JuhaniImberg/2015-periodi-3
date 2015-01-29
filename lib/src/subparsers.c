#include "tila.h"

struct Node *identifier_parser(struct Parser *parser,
                               struct Token *token) {
    return Node_identifier_new(token);
}

struct Node *assign_parser(struct Parser *parser,
                           struct Node *left,
                           struct Token *token) {
    ERROR(left->type != N_IDENTIFIER, "Left token must be an identifier");
}
