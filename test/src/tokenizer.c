#include "tilatest.h"

void do_test(char *src, int start[], int end[], enum TokenTypeEnum types[]) {
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
    int start[] = {0, 6, 11};
    int end[] = {5, 11, 12};
    enum TokenTypeEnum types[] = {T_IDENTIFIER, T_IDENTIFIER, T_EOL};
    do_test(src, start, end, types);
}
END_TEST

Suite *tokenizer_suite() {
    Suite *suite = suite_create("tokenizer_suite");
    TCase *tcase = tcase_create("case");

    tcase_add_test(tcase, test_tokenizer_identifier);

    suite_add_tcase(suite, tcase);
    return suite;
}
