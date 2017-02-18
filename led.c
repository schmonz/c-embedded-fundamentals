#include "led.h"

#include "syscalls.h"

void toggle_led(void)
{
    open("/dev/gpio0", O_WRONLY);
}
