#include "ra4m1.h"
#include "config.h"

#include "driver_clock.h"
#include "driver_gpio.h"
#include "driver_systick.h"


int main(void)
{
    clock_init();
    config_drivers();
    systick_init(clock_system_get(), 1000);

    uint64_t start_time = ticks_get();

    while(1)
    {
        if((ticks_get() - start_time) >= 100)
        {
            GPIO_ToggleOutputPin(PORT1, GPIO_PIN_NO_11);
            start_time = ticks_get();
        }
    }
}