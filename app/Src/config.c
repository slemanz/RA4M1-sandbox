#include "config.h"

/************************************************************
*                       DRIVERS                             *
*************************************************************/
#include "driver_clock.h"
#include "driver_gpio.h"
#include "driver_systick.h"

static const GPIO_PinConfig_t GPIO_ConfigTable[] = {
    {PORT1, GPIO_PIN_NO_11, GPIO_MODE_OUT,  GPIO_PIN_DRIVE_LOW, GPIO_PIN_OP_TYPE_CMOS, GPIO_PIN_PU_DISABLE, GPIO_PIN_PSEL_DEFAULT},
    {PORT3, GPIO_PIN_NO_4,  GPIO_MODE_OUT,  GPIO_PIN_DRIVE_LOW, GPIO_PIN_OP_TYPE_CMOS, GPIO_PIN_PU_DISABLE, GPIO_PIN_PSEL_DEFAULT},
    {PORT3, GPIO_PIN_NO_2,  GPIO_MODE_PSEL, GPIO_PIN_DRIVE_LOW, GPIO_PIN_OP_TYPE_CMOS, GPIO_PIN_PU_DISABLE, GPIO_PIN_P302_SCI2_TXD},
};

void config_drivers(void)
{
    clock_init();
    GPIO_Init_table(GPIO_ConfigTable, sizeof(GPIO_ConfigTable)/sizeof(GPIO_ConfigTable[0]));
    systick_init(clock_system_get(), 1000);
}