#include <stdio.h>
#include "config.h"

#include "bsp/led.h"
#include "core/simple-timer.h"

#include "driver_sci.h"
#include "driver_interrupt.h"

#include "interface_comm.h"

Comm_Interface_t *serial;

int main(void)
{
    config_drivers();
    serial = Comm_ProtocolGet(PROTOCOL_SCI2);

    simple_timer_t timer_blinky;
    simple_timer_t timer_ch;
    simple_timer_setup(&timer_blinky, 500, true);
    simple_timer_setup(&timer_ch, 1000, true);

    serial->init();

    printf("Init the board!\r\n");

    while(1)
    {
        if(simple_timer_has_elapsed(&timer_blinky)) led_toggle();

        if(serial->data_available())
        {
            uint8_t data_rx;
            serial->receive(&data_rx, 1);
            serial->send(&data_rx, 1);
            if(data_rx == '\r')
            {
                data_rx = '\n';
                serial->send(&data_rx, 1);
            }
        }
    }
}

// printf retarget
extern int __io_putchar(int ch)
{
    SCI_Write(SCI2, (uint8_t*)(&ch), 1);
    return ch;
}