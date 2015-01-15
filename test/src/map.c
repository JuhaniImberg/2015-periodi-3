#include "tilatest.h"

START_TEST (test_map_new)
{
    struct Map *map = Map_new();
    fail_if(!map, "Map_new didn't create a map");
    ck_assert_int_eq(map->size, 0);
    Map_delete(map);
}
END_TEST

START_TEST (test_map_light)
{
    struct Map *map = Map_new();
    fail_if(!map, "Map_new didn't allocate the map");

    void *val = malloc(sizeof(int));
    *((int*)val) = 333;
    Map_put(map, "test", val);
    ck_assert_int_eq(map->size, 1);
    ck_assert(Map_contains(map, "test"));
    ck_assert_int_eq(*((int*)Map_get(map, "test")), 333);
    Map_remove(map, "test");
    ck_assert_int_eq(map->size, 0);
    ck_assert(!Map_contains(map, "test"));
    free(val);
    Map_delete(map);
}
END_TEST

START_TEST (test_map_replace)
{
    struct Map *map = Map_new();
    int *val1 = (int*)malloc(sizeof(int));
    int *val2 = (int*)malloc(sizeof(int));
    *val1 = 333;
    *val2 = 666;
    Map_put(map, "test", val1);
    ck_assert_int_eq(*((int*)Map_get(map, "test")), 333);
    Map_put(map, "test", val2);
    ck_assert_int_eq(*((int*)Map_get(map, "test")), 666);
    free(val1);
    free(val2);
    Map_delete(map);
}
END_TEST

START_TEST (test_map_resize)
{
    struct Map *map = Map_new();
    const int testsize = 190;
    unsigned int original_size = map->allocated_size;
    char strs[testsize][9];
    for(int i = 0; i < testsize; i++) {
        sprintf(strs[i], "%i", i);
        Map_put(map, strs[i], (void *)strs[i]);
    }
    ck_assert_int_eq(map->size, testsize);
    ck_assert_int_gt(map->allocated_size, original_size);
    for(int i = 0; i < testsize; i++) {
        ck_assert(Map_contains(map, strs[i]));
    }
    Map_delete(map);
}
END_TEST

Suite *map_suite() {
    Suite *suite = suite_create("map_suite");
    TCase *tcase = tcase_create("case");

    tcase_add_test(tcase, test_map_new);
    tcase_add_test(tcase, test_map_light);
    tcase_add_test(tcase, test_map_replace);
    tcase_add_test(tcase, test_map_resize);

    suite_add_tcase(suite, tcase);
    return suite;
}
