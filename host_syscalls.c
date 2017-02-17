#include <limits.h>
#include <string.h>

#include "host_syscalls.h"


static struct {
    int  fake_return_value;
    int  spy_numcalls;
    char spy_path[PATH_MAX];
    int  spy_oflag;
} mock_open;

void mock_open_fake_return_value(int value) {
    mock_open.fake_return_value = value;
}

int mock_open_spy_numcalls() {
    return mock_open.spy_numcalls;
}

int mock_open_spy_oflag() {
    return mock_open.spy_oflag;
}

const char * mock_open_spy_path() {
    return mock_open.spy_path;
}

int open(const char *path, int oflag, ...) {
    strcpy(mock_open.spy_path, path);
    mock_open.spy_oflag = oflag;
    ++mock_open.spy_numcalls;
    return mock_open.fake_return_value;
}


static struct {
    int  fake_return_value;
    int  spy_numcalls;
    int  spy_fd;
    int  spy_request;
    int  spy_pin;
} mock_ioctl;

void mock_ioctl_fake_return_value(int value) {
    mock_ioctl.fake_return_value = value;
}

int mock_ioctl_spy_fd() {
    return mock_ioctl.spy_fd;
}

int mock_ioctl_spy_numcalls() {
    return mock_ioctl.spy_numcalls;
}

int mock_ioctl_spy_request() {
    return mock_ioctl.spy_request;
}

int mock_ioctl_spy_pin() {
    return mock_ioctl.spy_pin;
}

int ioctl(int fildes, unsigned long request, void *gpio_request) {
    (void)fildes;
    mock_ioctl.spy_fd = fildes;
    mock_ioctl.spy_request = request;
    mock_ioctl.spy_pin = ((struct gpio_req *)gpio_request)->gp_pin;
    ++mock_ioctl.spy_numcalls;
    return mock_ioctl.fake_return_value;
}


static struct {
    int  spy_numcalls;
    int  spy_fd;
} mock_close;

int mock_close_spy_numcalls() {
    return mock_close.spy_numcalls;
}

int mock_close_spy_fd() {
    return mock_close.spy_fd;
}

int close(int fildes) {
    mock_close.spy_fd = fildes;
    ++mock_close.spy_numcalls;
    return 99;
}


void mock_reset_all() {
    memset(&mock_open, 0, sizeof(mock_open));
    memset(&mock_ioctl, 0, sizeof(mock_ioctl));
    memset(&mock_close, 0, sizeof(mock_close));
}
