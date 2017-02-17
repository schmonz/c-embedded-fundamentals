#include <check.h>

#include "led.h"
#include "syscalls.h"

START_TEST(test_unit_nothing) {
    ck_assert_int_eq(2, 3);
} END_TEST

void setup(void) {
}

void teardown(void) {
}

TCase* tcase_unit(void) {
    TCase *tc = tcase_create("Unit Tests");

    tcase_add_checked_fixture(tc, setup, teardown);

    tcase_add_test(tc, test_unit_nothing);

    return tc;
}
