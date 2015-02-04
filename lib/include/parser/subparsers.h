#ifndef SUBPARSERS_H
#define SUBPARSERS_H

#include "tila.h"

/**
 * @brief Parses an identifier
 */
struct Node *identifier_parser(struct Parser *parser,
                               struct Token *token);

/**
 * @brief Parses an assignment
 */
struct Node *assign_parser(struct Parser *parser,
                           struct Node *left,
                           struct Token *token);

/**
 * @brief Parses a number
 */
struct Node *number_parser(struct Parser *parser,
                           struct Token *token);

/**
 * @brief Parses a string
 */
struct Node *string_parser(struct Parser *parser,
                           struct Token *token);

/**
 * @brief Parses a list of names of the arguments that are given to a function
 */
struct Node *argument_parser(struct Parser *parser,
                             struct Token *token);

/**
 * @brief Parses a function definition
 */
struct Node *function_parser(struct Parser *parser,
                             struct Node *left,
                             struct Token *token);

/**
 * @brief Parses a function call
 */
struct Node *call_parser(struct Parser *parser,
                         struct Node *left,
                         struct Token *token);

#endif
