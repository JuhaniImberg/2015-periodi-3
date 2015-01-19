#ifndef PARSER_H
#define PARSER_H

#include "tila.h"

/**
 * @brief Holds information about a parser
 * @field prefix A map of the prefix parsers
 * @field infix A map of the infix parsers
 * @field precedences A map of the infix parsers precedences
 * @field tokens A vector of the tokens that the parser uses
 * @field pos The position in the vector that is currently being used
 */
struct Parser {
    struct Map *prefix;
    struct Map *infix;
    struct Map *precedences;
    struct Vector *tokens;
    unsigned int pos;
};

/**
 * @brief A prefix parser
 */
typedef struct Node *(*PrefixParser)(struct Parser *parser,
                                      struct Token *token);
/**
 * @brief An infix parser
 */
typedef struct Node *(*InfixParser)(struct Parser *parser,
                                     struct Node *left,
                                     struct Token *token);

/**
 * @brief Creates a new parser
 * @param tokens The tokens the parser will use
 */
struct Parser *Parser_new(struct Vector *tokens);

/**
 * @brief Adds information about an infix parsers precedence
 * @param id The TokenTypeEnum type to have the precedence associated with
 * @param precedence The tokens operator precedence
 */
void Parser_add_precedence(struct Parser *parser, enum TokenTypeEnum id,
                           int precedence);

/**
 * @brief Adds a infix parser to the parser
 * @param id The TokenTypeEnum type to have the infix parser associated with
 * @param infix The infix parser function
 */
void Parser_add_infix(struct Parser *parser, enum TokenTypeEnum id,
                      InfixParser infix);

/**
 * @brief Adds a prefix parser to the parser
 * @param id The TokenTypeEnum type to have the prefix parser associated with
 * @param prefix The prefix parser function
 */
void Parser_add_prefix(struct Parser *parser, enum TokenTypeEnum id,
                      InfixParser prefix);

/**
 * @brief Parses the tokens to form a node expression that's made out of
 *        prefixes and infixes.
 * @param precedence Infix parsers that have a higher precedence than this
 *                   will be added to the node
 */
struct Node *Parser_parse_node(struct Parser *parser, int precedence);

/**
 * @brief Is the current token of the type id
 * @param id The type that the token is checked against
 * @returns True if the type matches
 */
bool Parser_is_next(struct Parser *parser, enum TokenTypeEnum id);

/**
 * @brief If the current token is of the type id, it gets consumed
 * @param id The type that the token is checked against
 * @returns True if the type matches
 */
bool Parser_match(struct Parser *parser, enum TokenTypeEnum id);
struct Token *Parser_require(struct Parser *parser, enum TokenTypeEnum id);
struct Token *Parser_consume(struct Parser *parser);
struct Token *Parser_current(struct Parser *parser);
int Parser_precedence(struct Parser *parser);
void Parser_delete(struct Parser *parser);

#endif
