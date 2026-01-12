#include "bsp/led.h"
#include "interface_io.h"

static IO_Interface_t *led_pin;

void led_setup(void)
{
    led_pin = IO_Interface_get(IO1);
}

void led_toggle(void)
{
    if(led_pin != NULL) led_pin->toggle();
}