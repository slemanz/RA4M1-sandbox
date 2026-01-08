#include "interface_comm.h"
#include "interface_instances.h"

#include "shared/ring-buffer.h"
#include "driver_sci.h"
#include "driver_gpio.h"
#include "driver_interrupt.h"

// Ring buffer
#define SERIAL_BUFFER_SIZE     128

/************************************************************
*                       SCI2                                *
*************************************************************/

static ring_buffer_t rb_sci2 = {0U};
static uint8_t data_buffer_sci2[SERIAL_BUFFER_SIZE] = {0U};
static uint8_t sci2_is_init = 0;

void sci2_protocol_init(void)
{
    ring_buffer_setup(&rb_sci2, data_buffer_sci2, SERIAL_BUFFER_SIZE);

    GPIO_PinConfig_t SCI2_Pins;
    SCI2_Pins.pPORT = PORT3;
    SCI2_Pins.GPIO_PinNumber = GPIO_PIN_NO_2;
    SCI2_Pins.GPIO_PinMode = GPIO_MODE_PSEL;
    SCI2_Pins.GPIO_PinDrive = GPIO_PIN_DRIVE_LOW;
    SCI2_Pins.GPIO_PinOPType = GPIO_PIN_OP_TYPE_CMOS;
    SCI2_Pins.GPIO_PinPuControl = GPIO_PIN_PU_DISABLE;
    SCI2_Pins.GPIO_PeriphSel = GPIO_PIN_P302_SCI2_TXD;
    GPIO_Init(&SCI2_Pins);

    SCI2_Pins.GPIO_PinNumber = GPIO_PIN_NO_1;
    SCI2_Pins.GPIO_PeriphSel = GPIO_PIN_P301_SCI2_RXD;
    GPIO_Init(&SCI2_Pins);

    SCI_Config_t SCI2_Config;
    SCI2_Config.pSCIx = SCI2;
    SCI2_Config.SCI_Baud = SCI_STD_BAUD_115200;
    SCI2_Config.SCI_NoOfStopBits = SCI_STOPBITS_1;
    SCI2_Config.SCI_ParityControl = SCI_PARITY_DISABLE;
    SCI2_Config.SCI_Mode = SCI_MODE_TXRX;
    SCI_Init(&SCI2_Config);
    SCI_InterruptConfig(SCI2, SCI_INTERRUPT_RIE, ENABLE);

    interrupt_Config(IRQ_NO_0, ENABLE);
    icu_config(ICU_EVENT_NO_0, ICU_EVENT_SCI2_RXI);

    sci2_is_init = 1;
}


void sci2_protocol_send(uint8_t *data, uint32_t Len)
{
    if(!sci2_is_init) sci2_protocol_init();
    SCI_Write(SCI2, data, Len);
}

uint8_t sci2_protocol_receive(uint8_t *buffer, uint32_t Len)
{
    if(!sci2_is_init) sci2_protocol_init();

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
    if(!sci2_is_init) sci2_protocol_init();
    return !ring_buffer_empty(&rb_sci2);
}

void EVENT0_IRQHandler(void)
{
    uint8_t received_data;
    SCI_ReadByte(SCI2, &received_data);
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