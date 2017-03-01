#include "syscalls.h"

void led_toggle() {
    open("/dev/gpio0", O_WRONLY);
}
