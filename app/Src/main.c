#include "config.h"

#include "bsp/led.h"
#include "core/simple-timer.h"
#include "core/cli.h"
#include "core/uprint.h"

int main(void)
{
    config_app();

    simple_timer_t timer_blinky;
    simple_timer_t timer_ch;
    simple_timer_setup(&timer_blinky, 500, true);
    simple_timer_setup(&timer_ch, 1000, true);

    uprint("Init the board!\r\n");
    
    while(1)
    {
        if(simple_timer_has_elapsed(&timer_blinky))
        {
            led_toggle();
        }

        cli_update();
    }
}
