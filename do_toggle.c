#include <stdio.h>

#include "led.h"

int main(void)
{
    toggle_led();
    fprintf(stderr, "just called toggle_led();\n");
    return 0;
}
