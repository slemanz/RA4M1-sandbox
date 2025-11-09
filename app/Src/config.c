#include "config.h"

// drivers
#include "driver_gpio.h"

void config_drivers(void)
{
    GPIO_PinConfig_t gpio111;
    gpio111.pPORT = PORT1;
    gpio111.GPIO_PinNumber = GPIO_PIN_NO_11;
    gpio111.GPIO_PinMode = GPIO_MODE_OUT;
    gpio111.GPIO_PinPuControl = GPIO_PIN_PU_DISABLE;
    gpio111.GPIO_PinOPType = GPIO_PIN_OP_TYPE_CMOS;
    gpio111.GPIO_PinDrive = GPIO_PIN_DRIVE_LOW;
    gpio111.GPIO_PeriphSel = GPIO_PIN_PSEL_DEFAULT;
    GPIO_Init(&gpio111);
}