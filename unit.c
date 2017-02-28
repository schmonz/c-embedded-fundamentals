#include <check.h>

#include "led.h"
#include "syscalls.h"

START_TEST(it_opens_gpio_device_for_write) {
    ck_assert_int_eq(mock_open_spy_numcalls(), 0);
    ck_assert_str_eq(mock_open_spy_path(), "");
    ck_assert_int_eq(mock_open_spy_oflag(), 0);

    led_toggle();

    ck_assert_int_eq(mock_open_spy_numcalls(), 1);
    ck_assert_str_eq(mock_open_spy_path(), "/dev/gpio0");
    ck_assert_int_eq(mock_open_spy_oflag(), O_WRONLY);
} END_TEST

START_TEST(it_stops_if_open_fails) {
    mock_open_fake_return_value(-1);

    led_toggle();

    ck_assert_int_eq(mock_open_spy_numcalls(), 1);
    ck_assert_int_eq(mock_ioctl_spy_numcalls(), 0);
} END_TEST

START_TEST(it_calls_ioctl_if_open_succeeds) {
    mock_open_fake_return_value(5);

    led_toggle();

    ck_assert_int_eq(mock_open_spy_numcalls(), 1);
    ck_assert_int_eq(mock_ioctl_spy_numcalls(), 1);
} END_TEST

START_TEST(it_ioctls_gpio_device_to_toggle_our_pin) {
    mock_open_fake_return_value(44);

    led_toggle();

    ck_assert_int_eq(mock_ioctl_spy_fd(), 44);
    ck_assert_int_eq(mock_ioctl_spy_request(), GPIOTOGGLE);
    ck_assert_int_eq(mock_ioctl_spy_pin(), 16);
} END_TEST

START_TEST(it_closes_gpio_device_if_ioctl_succeeds) {
    mock_open_fake_return_value(33);
    mock_ioctl_fake_return_value(1);

    led_toggle();

    ck_assert_int_eq(mock_open_spy_numcalls(), 1);
    ck_assert_int_eq(mock_ioctl_spy_numcalls(), 1);
    ck_assert_int_eq(mock_close_spy_numcalls(), 1);
    ck_assert_int_eq(mock_close_spy_fd(), 33);
} END_TEST

START_TEST(it_closes_gpio_device_if_ioctl_fails) {
    mock_open_fake_return_value(22);
    mock_ioctl_fake_return_value(-1);

    led_toggle();

    ck_assert_int_eq(mock_open_spy_numcalls(), 1);
    ck_assert_int_eq(mock_ioctl_spy_numcalls(), 1);
    ck_assert_int_eq(mock_close_spy_numcalls(), 1);
    ck_assert_int_eq(mock_close_spy_fd(), 22);
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
