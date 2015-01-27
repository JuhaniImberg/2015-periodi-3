#include "tilatest.h"

void do_test(char *src, unsigned int start[],
             int unsigned end[], enum TokenTypeEnum types[]) {
    struct Tokenizer *ti = Tokenizer_new(src);
    Tokenizer_tokenize(ti);
    unsigned int len = Vector_size(ti->tokens);
    for(unsigned int i = 0; i < len; i++) {
        struct Token *tkn = Vector_get(ti->tokens, i);
        ck_assert_int_eq(start[i], tkn->start);
        ck_assert_int_eq(end[i], tkn->end);
        ck_assert_int_eq(types[i], tkn->type->id);
    }
    Tokenizer_delete(ti);
}

START_TEST (test_tokenizer_identifier)
{
    char *src = "hello world";
    unsigned int start[] = {0, 6, 11};
    unsigned int end[] = {5, 11, 12};
    enum TokenTypeEnum types[] = {T_IDENTIFIER, T_IDENTIFIER, T_EOL};
    do_test(src, start, end, types);
}
END_TEST

START_TEST (test_tokenizer_number)
{
    char *src = "312 231";
    unsigned int start[] = {0, 4, 7};
    unsigned int end[] = {3, 7, 8};
    enum TokenTypeEnum types[] = {T_NUMBER, T_NUMBER, T_EOL};
    do_test(src, start, end, types);
}
END_TEST

START_TEST (test_tokenizer_string)
{
    char *src = "\"a\" \"b\"";
    unsigned int start[] = {0, 4, 7};
    unsigned int end[] = {3, 7, 8};
    enum TokenTypeEnum types[] = {T_STRING, T_STRING, T_EOL};
    do_test(src, start, end, types);
}
END_TEST

START_TEST (test_tokenizer_newline)
{
    char *src = "hello\nworld";
    unsigned int start[] = {0, 5, 6, 11};
    unsigned int end[] = {5, 6, 11, 12};
    enum TokenTypeEnum types[] = {T_IDENTIFIER, T_EOL, T_IDENTIFIER, T_EOL};
    do_test(src, start, end, types);
}
END_TEST

START_TEST (test_tokenizer_comment)
{
    char *src = "# hello world";
    unsigned int start[] = {13};
    unsigned int end[] = {14};
    enum TokenTypeEnum types[] = {T_EOL};
    do_test(src, start, end, types);
}
END_TEST

START_TEST (test_tokenizer_indent)
{
    char *src = "  hello\n    world";
    unsigned int start[] = {0, 2, 7, 8, 12, 17};
    unsigned int end[] = {2, 7, 8, 12, 17, 18};
    enum TokenTypeEnum types[] = {T_INDENT, T_IDENTIFIER, T_EOL, T_INDENT,
                                  T_IDENTIFIER, T_EOL};
    do_test(src, start, end, types);
}
END_TEST

START_TEST (test_tokenizer_operators)
{
    char *src = "+-*/=?!><";
    unsigned int start[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    unsigned int end[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    enum TokenTypeEnum types[] = {T_ADD, T_SUB, T_MUL, T_DIV, T_SET, T_COND,
                                  T_NOT, T_GT, T_LT, T_EOL};
    do_test(src, start, end, types);
}
END_TEST

START_TEST (test_tokenizer_long_operators)
{
    char *src = "==!=>=<=!?||&&->";
    unsigned int start[] = {0, 2, 4, 6, 8, 10, 12, 14, 16};
    unsigned int end[] = {2, 4, 6, 8, 10, 12, 14, 16, 17};
    enum TokenTypeEnum types[] = {T_EQ, T_NOTEQ, T_GTOE, T_LTOE, T_NOTCOND,
                                   T_OR, T_AND, T_FN, T_EOL};
    do_test(src, start, end, types);
}
END_TEST

START_TEST (test_token_content)
{
    char *src = "hello world";
    struct Tokenizer *ti = Tokenizer_new(src);
    Tokenizer_tokenize(ti);
    ck_assert(strcmp(Token_content(Vector_get(ti->tokens, 0), src), "hello") == 0);
    ck_assert(strcmp(Token_content(Vector_get(ti->tokens, 1), src), "world") == 0);
    Tokenizer_delete(ti);
}
END_TEST

Suite *tokenizer_suite() {
    Suite *suite = suite_create("tokenizer_suite");
    TCase *tcase = tcase_create("case");

    tcase_add_test(tcase, test_tokenizer_identifier);
    tcase_add_test(tcase, test_tokenizer_number);
    tcase_add_test(tcase, test_tokenizer_string);
    tcase_add_test(tcase, test_tokenizer_newline);
    tcase_add_test(tcase, test_tokenizer_comment);
    tcase_add_test(tcase, test_tokenizer_indent);
    tcase_add_test(tcase, test_tokenizer_operators);
    tcase_add_test(tcase, test_tokenizer_long_operators);

    tcase_add_test(tcase, test_token_content);


    suite_add_tcase(suite, tcase);
    return suite;
}
