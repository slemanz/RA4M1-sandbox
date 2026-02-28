#include "bsp/led.h"

static uint8_t led_pin;

void led_setup(uint8_t io_pin)
{
    led_pin = io_pin;
}

void led_toggle(void)
{
   IO_toggle(led_pin);
}