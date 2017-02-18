#include <check.h>

#include "led.h"
#include "syscalls.h"

START_TEST(it_calls_open_with_right_arguments) {
    set_num_mock_open_calls(0);
    ck_assert_int_eq(0, get_num_mock_open_calls());
    toggle_led();
    ck_assert_int_eq(1, get_num_mock_open_calls());
} END_TEST

void setup(void) {
}

void teardown(void) {
}

TCase* tcase_unit(void) {
    TCase *tc = tcase_create("Unit Tests");

    tcase_add_checked_fixture(tc, setup, teardown);

    tcase_add_test(tc, it_calls_open_with_right_arguments);

    return tc;
}
