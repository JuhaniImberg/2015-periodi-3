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
    ck_assert_int_eq(Vector_size(vector), 1);
    Vector_add(vector, (void *)val2);
    ck_assert_int_eq(Vector_size(vector), 2);
    ck_assert(strcmp(Vector_get(vector, 0), val1) == 0);
    ck_assert(strcmp(Vector_get(vector, 1), val2) == 0);

    Vector_set(vector, 321, "inva"); // This should do nothing
    Vector_set(vector, 0, "rsa");

    ck_assert(strcmp(Vector_remove(vector, 0), "rsa") == 0);
    ck_assert_int_eq(Vector_size(vector), 1);
    ck_assert(strcmp(Vector_remove(vector, 0), val2) == 0);
    ck_assert_int_eq(Vector_size(vector), 0);
    ck_assert(Vector_empty(vector));

    ck_assert(Vector_get(vector, 321) == NULL);
    ck_assert(Vector_remove(vector, 321) == NULL);

    Vector_delete(vector);
}
END_TEST

START_TEST (test_vector_resize)
{
    struct Vector *vector = Vector_new();
    unsigned int testsize = 190;
    unsigned int original_size = vector->allocated_size;
    char strs[testsize][9];
    for(unsigned int i = 0; i < testsize; i++) {
        sprintf(strs[i], "%i", i);
        Vector_add(vector, (void *)strs[i]);
    }
    ck_assert_int_eq(vector->size, testsize);
    ck_assert(vector->allocated_size > original_size);
    for(unsigned int i = 0; i < testsize; i++) {
        ck_assert(strcmp(Vector_remove(vector, 0), strs[i]) == 0);
    }
    ck_assert_int_eq(vector->size, 0);
    Vector_delete(vector);
}
END_TEST

START_TEST (test_vector_insert)
{
    struct Vector *vector = Vector_new();
    Vector_add(vector, "start");
    Vector_add(vector, "end");
    Vector_insert(vector, 1, "middle");
    ck_assert_int_eq(vector->size, 3);
    ck_assert(strcmp(Vector_get(vector, 0), "start") == 0);
    ck_assert(strcmp(Vector_get(vector, 1), "middle") == 0);
    ck_assert(strcmp(Vector_get(vector, 2), "end") == 0);
    Vector_clear(vector);
    // Vector shouldn't grow from invalid insert
    Vector_insert(vector, 321, "wolo");
    ck_assert(Vector_empty(vector));
    Vector_delete(vector);
}
END_TEST

START_TEST (test_vector_stack)
{
    struct Vector *vector = Vector_new();
    Vector_push(vector, "3");
    Vector_push(vector, "2");
    Vector_push(vector, "1");
    ck_assert(strcmp(Vector_top(vector), "1") == 0);
    ck_assert(strcmp(Vector_pop(vector), "1") == 0);
    ck_assert(strcmp(Vector_pop(vector), "2") == 0);
    ck_assert(strcmp(Vector_pop(vector), "3") == 0);
    ck_assert(Vector_pop(vector) == NULL);
    ck_assert(Vector_top(vector) == NULL);
    Vector_delete(vector);
}
END_TEST

Suite *vector_suite() {
    Suite *suite = suite_create("vector_suite");
    TCase *tcase = tcase_create("case");

    tcase_add_test(tcase, test_vector_new);
    tcase_add_test(tcase, test_vector_basic);
    tcase_add_test(tcase, test_vector_resize);
    tcase_add_test(tcase, test_vector_insert);
    tcase_add_test(tcase, test_vector_stack);

    suite_add_tcase(suite, tcase);
    return suite;
}
