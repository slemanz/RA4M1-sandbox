#include "config.h"

/************************************************************
*                       DRIVERS                             *
*************************************************************/
#include "driver_clock.h"
#include "driver_gpio.h"

static const GPIO_PinConfig_t GPIO_ConfigTable[] = {
    {PORT1, GPIO_PIN_NO_11, GPIO_MODE_OUT,  GPIO_PIN_DRIVE_LOW, GPIO_PIN_OP_TYPE_CMOS, GPIO_PIN_PU_DISABLE, GPIO_PIN_PSEL_DEFAULT},
    {PORT3, GPIO_PIN_NO_4,  GPIO_MODE_OUT,  GPIO_PIN_DRIVE_LOW, GPIO_PIN_OP_TYPE_CMOS, GPIO_PIN_PU_DISABLE, GPIO_PIN_PSEL_DEFAULT},
};

/************************************************************
*                      INTERFACE                            *
*************************************************************/

#include "interface_comm.h"

Comm_Interface_t *serial = NULL;

void config_interface(void)
{
    serial = Comm_ProtocolGet(PROTOCOL_SCI2);
}

// printf retarget
extern int __io_putchar(int ch)
{
    if(serial != NULL) serial->send((uint8_t*)&ch, 1);
    return ch;
}

/************************************************************
*                         CORE                              *
*************************************************************/
#include "core/cli.h"
#include "core/simple-timer.h"

const command_t commands_table[] = {
    {"help", cli_help, "List all commands."},
};

void config_core(void)
{
    cli_setup(Comm_ProtocolGet(PROTOCOL_SCI2), (command_t*)commands_table, 1);
}

/************************************************************
*                         APP                               *
*************************************************************/

void config_app(void)
{
    clock_init();
    GPIO_Init_table(GPIO_ConfigTable, sizeof(GPIO_ConfigTable)/sizeof(GPIO_ConfigTable[0]));

    config_interface();
    config_core();
}