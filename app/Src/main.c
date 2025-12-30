#include <stdio.h>
#include "config.h"

#include "bsp/led.h"
#include "core/simple-timer.h"

#include "driver_sci.h"


int main(void)
{
    config_drivers();
    sci2_init();

    simple_timer_t timer_blinky;
    simple_timer_t timer_ch;
    simple_timer_setup(&timer_blinky, 500, true);
    simple_timer_setup(&timer_ch, 1000, true);

    printf("Init the board!\r\n");

    while(1)
    {
        if(simple_timer_has_elapsed(&timer_blinky)) led_toggle();

        //if(simple_timer_has_elapsed(&timer_ch)) sci2_write_byte('A');
    }
}

// printf retarget
extern int __io_putchar(int ch)
{
    sci2_write_byte((uint8_t)ch);
    return ch;
}