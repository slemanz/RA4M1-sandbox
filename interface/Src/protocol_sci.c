#include "interface_comm.h"
#include "interface_instances.h"

#include "shared/ring-buffer.h"
#include "driver_sci.h"
#include "driver_interrupt.h"

// Ring buffer
#define SERIAL_BUFFER_SIZE     128

/************************************************************
*                       SCI2                                *
*************************************************************/

static ring_buffer_t rb_sci2 = {0U};
static uint8_t data_buffer_sci2[SERIAL_BUFFER_SIZE] = {0U};

void sci2_protocol_init(void)
{
    ring_buffer_setup(&rb_sci2, data_buffer_sci2, SERIAL_BUFFER_SIZE);

    sci2_init();
    
    interrupt_Config(IRQ_NO_0, ENABLE);
    icu_config(ICU_EVENT_NO_0, ICU_EVENT_SCI2_RXI);
}


void sci2_protocol_send(uint8_t *data, uint32_t Len)
{
    sci2_write(data, Len);
}

uint8_t sci2_protocol_receive(uint8_t *buffer, uint32_t Len)
{
    if(Len == 0)
    {
        return 0;
    }

    for(uint8_t bytes_read = 0; bytes_read < Len; bytes_read++)
    {
        if(!ring_buffer_read(&rb_sci2, &buffer[bytes_read])) return bytes_read;
    }

    return Len;
}

uint8_t sci2_protocol_data_available(void)
{
    return !ring_buffer_empty(&rb_sci2);
}

void EVENT0_IRQHandler(void)
{
    uint8_t received_data = SCI2->RDR;
    ring_buffer_write(&rb_sci2, received_data);
    icu_clear_irq(ICU_EVENT_NO_0);
}


/************************************************************
*                     WRAPPER                               *
*************************************************************/

const Comm_Interface_t sci2_protocol = {
    .init = sci2_protocol_init,
    .send = sci2_protocol_send,
    .receive = sci2_protocol_receive,
    .data_available = sci2_protocol_data_available,
    .deinit = NULL
};