#include "tilatest.h"

START_TEST (test_vector_new)
{
    struct Vector *vector = Vector_new();
    fail_if(!vector, "Vector_new didn't create a vector");
    ck_assert_int_eq(vector->size, 0);
    Vector_delete(vector);
}
END_TEST

START_TEST (test_vector_basic)
{
    struct Vector *vector = Vector_new();
    char *val1 = "asd";
    char *val2 = "dsa";
    Vector_add(vector, (void *)val1);
    ck_assert_int_eq(vector->size, 1);
    Vector_add(vector, (void *)val2);
    ck_assert_int_eq(vector->size, 2);
    ck_assert(strcmp(Vector_get(vector, 0), val1) == 0);
    ck_assert(strcmp(Vector_get(vector, 1), val2) == 0);

    ck_assert(strcmp(Vector_remove(vector, 0), val1) == 0);
    ck_assert_int_eq(vector->size, 1);
    ck_assert(strcmp(Vector_remove(vector, 0), val2) == 0);
    ck_assert_int_eq(vector->size, 0);

    Vector_delete(vector);
}
END_TEST

START_TEST (test_vector_resize)
{
    struct Vector *vector = Vector_new();
    const int testsize = 190;
    unsigned int original_size = vector->allocated_size;
    char strs[testsize][9];
    for(int i = 0; i < testsize; i++) {
        sprintf(strs[i], "%i", i);
        Vector_add(vector, (void *)strs[i]);
    }
    ck_assert_int_eq(vector->size, testsize);
    ck_assert_int_gt(vector->allocated_size, original_size);
    for(int i = 0; i < testsize; i++) {
        ck_assert(strcmp(Vector_remove(vector, 0), strs[i]) == 0);
    }
    ck_assert_int_eq(vector->size, 0);
    Vector_delete(vector);
}
END_TEST

Suite *vector_suite() {
    Suite *suite = suite_create("vector_suite");
    TCase *tcase = tcase_create("case");

    tcase_add_test(tcase, test_vector_new);
    tcase_add_test(tcase, test_vector_basic);
    tcase_add_test(tcase, test_vector_resize);

    suite_add_tcase(suite, tcase);
    return suite;
}
