#include "ra4m1.h"
#include "config.h"

#include "driver_gpio.h"


int main(void)
{
    config_drivers();

    while(1)
    {
        GPIO_ToggleOutputPin(PORT1, GPIO_PIN_NO_11);
        for(uint32_t i = 0; i < 30000; i++) __asm("NOP");
    }
}