#include <string.h>
#include <err.h>

#include "led.h"

#include "syscalls.h"

void toggle_led(void)
{
    struct gpio_req request;
    memset(&request, 0, sizeof(struct gpio_req));
    request.gp_pin = 16;
	int fd = open("/dev/gpio0", O_RDWR);
    ioctl(fd, GPIOTOGGLE, &request);
    close(fd);
}
