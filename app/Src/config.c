#include "config.h"

/************************************************************
*                       DRIVERS                             *
*************************************************************/
#include "driver_clock.h"


/************************************************************
*                      INTERFACE                            *
*************************************************************/

#include "interface/interface.h"
#include "interface_defines.h"

Comm_Interface_t *serial = NULL;

void config_interface(void)
{
    serial = Comm_ProtocolGet(INTERFACE_PROTOCOL_SCI2);
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
#include "core/uprint.h"
#include "core/cli.h"
#include "core/simple-timer.h"

const command_t commands_table[] = {
    {"help", cli_help, "List all commands."},
};

void config_core(void)
{
    uprint_setup(Comm_ProtocolGet(INTERFACE_PROTOCOL_SCI2));
    cli_setup(Comm_ProtocolGet(INTERFACE_PROTOCOL_SCI2), (command_t*)commands_table, 1);
}

/************************************************************
*                         APP                               *
*************************************************************/

#include "bsp/led.h"

void config_app(void)
{
    clock_init();

    config_interface();
    config_core();
    led_setup(IO_Interface_get(INTERFACE_IO_1));
}