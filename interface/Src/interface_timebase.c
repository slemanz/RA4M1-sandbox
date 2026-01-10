#include "interface_timebase.h"
#include "driver_systick.h"
#include "driver_clock.h"

uint8_t timebase_is_init = 0;

const static timebase_interface_t timer_systick = {
    .get = ticks_get,
    .deinit = NULL
};



timebase_interface_t *timebase_get(void)
{
    if(timebase_is_init == 0) systick_init(clock_system_get(), 1000);

    return (timebase_interface_t*)&timer_systick;
}