#include <stdio.h>

#include "led.h"

int main() {
    led_toggle();
    fprintf(stderr, "just called led_toggle()\n");
    return 0;
}
