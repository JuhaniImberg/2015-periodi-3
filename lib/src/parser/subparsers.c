#include "tila.h"

struct Node *identifier_parser(struct Parser *parser __attribute__((unused)),
                               struct Token *token) {
    return IdentifierNode_new(token);
}

struct Node *assign_parser(struct Parser *parser,
                           struct Node *left,
                           struct Token *token) {
    ASSERT(left->type != N_IDENTIFIER, "Left token must be an identifier");
    struct Node *right = Parser_parse_node(parser, 0);
    return AssignNode_new(left, token, right);
}

struct Node *number_parser(struct Parser *parser __attribute__((unused)),
                           struct Token *token) {
    return NumberNode_new(token);
}
