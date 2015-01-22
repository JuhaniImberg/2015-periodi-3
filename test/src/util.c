#include "tilatest.h"

START_TEST (test_util_is)
{
    ck_assert(t_is_alpha('A'));
    ck_assert(t_is_alpha('Z'));
    ck_assert(t_is_alpha('a'));
    ck_assert(t_is_alpha('z'));
    ck_assert(t_is_alpha('_'));

    ck_assert(!t_is_alpha('5'));

    ck_assert(t_is_digit('1'));
    ck_assert(t_is_digit('9'));

    ck_assert(!t_is_digit('t'));
}
END_TEST

START_TEST (test_util_hash)
{
    unsigned long a = string_hash((void *)"hello");
    unsigned long b = string_hash((void *)"world");
    ck_assert(a != b);
}
END_TEST

Suite *util_suite() {
    Suite *suite = suite_create("util_suite");
    TCase *tcase = tcase_create("case");

    tcase_add_test(tcase, test_util_is);
    tcase_add_test(tcase, test_util_hash);

    suite_add_tcase(suite, tcase);
    return suite;
}
