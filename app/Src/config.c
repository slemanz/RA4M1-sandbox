#include "config.h"

/************************************************************
*                       DRIVERS                             *
*************************************************************/
#include "driver_clock.h"
#include "driver_gpio.h"


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

    config_interface();
    config_core();
}