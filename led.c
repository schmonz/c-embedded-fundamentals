#include "syscalls.h"

void led_toggle() {
    int fd = open("/dev/gpio0", O_WRONLY);
    close(fd);
}
