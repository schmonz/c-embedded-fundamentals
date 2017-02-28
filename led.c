#include <string.h>

#include "syscalls.h"

void led_toggle() {
    struct gpio_req myrequest;
    int file_descriptor;

    if (-1 == (file_descriptor = open("/dev/gpio0", O_WRONLY)))
        return;

    memset(&myrequest, 0, sizeof(myrequest));
    myrequest.gp_pin = 16;
    ioctl(file_descriptor, GPIOTOGGLE, &myrequest);

    close(file_descriptor);
}
