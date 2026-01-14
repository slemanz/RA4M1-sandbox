#include "bsp/led.h"

static IO_Interface_t *led_pin;

void led_setup(IO_Interface_t *io_pin)
{
    led_pin = io_pin;
}

void led_toggle(void)
{
    if(led_pin != NULL) led_pin->toggle();
}