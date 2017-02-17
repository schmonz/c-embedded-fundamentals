#include <check.h>

TCase* tcase_acceptance(void);
TCase* tcase_unit(void);

Suite* led_toggle_suite(void) {
    Suite *s = suite_create("Raspberry Pi LED Toggle");

    suite_add_tcase(s, tcase_acceptance());
    suite_add_tcase(s, tcase_unit());

    return s;
}

int main(void) {
    int number_failed;

    SRunner *sr = srunner_create(led_toggle_suite());
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return number_failed;
}
