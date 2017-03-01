#include <check.h>

#include "led.h"
#include "syscalls.h"

START_TEST(it_opens_gpio_device_for_write) {
    mock_open_fake_return_value(37);

    ck_assert_int_eq(mock_open_spy_numcalls(), 0);
    ck_assert_str_eq(mock_open_spy_path(), "");
    ck_assert_int_eq(mock_open_spy_oflag(), 0);

    led_toggle();

    ck_assert_int_eq(mock_open_spy_numcalls(), 1);
    ck_assert_str_eq(mock_open_spy_path(), "/dev/gpio0");
    ck_assert_int_eq(mock_open_spy_oflag(), O_WRONLY);

    ck_assert_int_eq(mock_close_spy_numcalls(), 1);
    ck_assert_int_eq(mock_close_spy_fd(), 37);
} END_TEST

START_TEST(it_stops_if_open_fails) {
    // if open() returns its error code, don't proceed to call ioctl()
} END_TEST

START_TEST(it_calls_ioctl_if_open_succeeds) {
} END_TEST

START_TEST(it_ioctls_gpio_device_to_toggle_our_pin) {
} END_TEST

START_TEST(it_closes_gpio_device_if_ioctl_succeeds) {
} END_TEST

START_TEST(it_closes_gpio_device_if_ioctl_fails) {
} END_TEST

void setup(void) {
    mock_reset_all();
}

void teardown(void) {
}

TCase* tcase_unit(void) {
    TCase *tc = tcase_create("Unit Tests");

    tcase_add_checked_fixture(tc, setup, teardown);

    tcase_add_test(tc, it_opens_gpio_device_for_write);
    tcase_add_test(tc, it_stops_if_open_fails);
    tcase_add_test(tc, it_calls_ioctl_if_open_succeeds);
    tcase_add_test(tc, it_ioctls_gpio_device_to_toggle_our_pin);
    tcase_add_test(tc, it_closes_gpio_device_if_ioctl_succeeds);
    tcase_add_test(tc, it_closes_gpio_device_if_ioctl_fails);

    return tc;
}
