#include <string.h>

#include "syscalls.h"

static void toggle_pin(int pin) {
    int fd = open("/dev/gpio0", O_WRONLY);

    struct gpio_req my_req;
    //memset(&my_req, 0, sizeof(struct gpio_req));
    my_req.gp_pin = pin;
    ioctl(fd, GPIOTOGGLE, &my_req);

    close(fd);
}

void led_toggle() {
    int LED_PIN = 16;
    toggle_pin(LED_PIN);
}
