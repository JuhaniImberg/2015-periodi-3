#include "tilatest.h"

int main() {
    int number_failed = 0;
    SRunner *runner = srunner_create(map_suite());
    srunner_add_suite(runner, vector_suite());
    srunner_add_suite(runner, util_suite());
    srunner_add_suite(runner, tokenizer_suite());
    srunner_run_all(runner, CK_NORMAL);
    number_failed += srunner_ntests_failed(runner);
    srunner_free(runner);
    return number_failed;
}
