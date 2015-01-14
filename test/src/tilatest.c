#include "tilatest.h"

int main() {
    int number_failed = 0;
    Suite *suite = map_suite();
    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    number_failed += srunner_ntests_failed(runner);
    srunner_free(runner);
    return number_failed;
}
