#include "tila.h"

struct Node *identifier_parser(struct Parser *parser,
                               struct Token *token) {
    return Node_identifier_new(token);
}

struct Node *assign_parser(struct Parser *parser,
                           struct Node *left,
                           struct Token *token) {
    ASSERT(left->type != N_IDENTIFIER, "Left token must be an identifier");
    struct Node *right = Parser_parse_node(parser, 0);
    return Node_assign_new(left, token, right);
}

struct Node *number_parser(struct Parser *parser,
                           struct Token *token) {
    return Node_number_new(token);
}
