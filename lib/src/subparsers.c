#include "tila.h"

struct Node *identifier_parser(struct Parser *parser,
                               struct Token *token) {
    return Node_identifier_new(token);
}
