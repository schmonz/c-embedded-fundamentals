#include <stdio.h>

#include "led.h"

int main(void) {
    led_toggle();
    fprintf(stderr, "just called led_toggle()\n");
}
