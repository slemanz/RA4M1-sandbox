#include "config.h"

#include "bsp/led.h"
#include "core/simple-timer.h"


int main(void)
{
    config_drivers();

    simple_timer_t timer_blinky;
    simple_timer_setup(&timer_blinky, 500, true);

    while(1)
    {
        if(simple_timer_has_elapsed(&timer_blinky)) led_toggle();
    }
}