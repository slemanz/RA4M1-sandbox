#include "bsp/led.h"
#include "driver_gpio.h"

void led_toggle(void)
{
    GPIO_ToggleOutputPin(PORT3, GPIO_PIN_NO_4);
}