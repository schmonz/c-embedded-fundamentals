#include <check.h>

#include "led.h"

START_TEST(test_acceptance_nothing) {
    toggle_led();
} END_TEST

TCase* tcase_acceptance(void) {
    TCase *tc = tcase_create("Acceptance Tests");

    tcase_add_test(tc, test_acceptance_nothing);

    return tc;
}
