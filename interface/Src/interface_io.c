#include "interface/interface.h"
#include "interface_instances.h"
#include "interface_defines.h"
#include "driver_gpio.h"

/************************************************************
*                     PIN_DEFAULT                           *
*************************************************************/

#define IO0_INIT_MASK           (1U << 0)
#define IO1_INIT_MASK           (1U << 1)

static uint32_t port_is_init_var = 0;

static uint8_t port_is_init(uint16_t mask)
{
    return (port_is_init_var & mask);
}

/************************************************************
*                         IO0                               *
*************************************************************/

static void io0_init(void)
{
    GPIO_PinConfig_t io0_config;
    io0_config.pPORT = PORT1;
    io0_config.GPIO_PinNumber = GPIO_PIN_NO_11;
    io0_config.GPIO_PinMode = GPIO_MODE_OUT;
    io0_config.GPIO_PinDrive = GPIO_PIN_DRIVE_LOW;
    io0_config.GPIO_PinOPType = GPIO_PIN_OP_TYPE_CMOS;
    io0_config.GPIO_PinPuControl = GPIO_PIN_PU_DISABLE;
    io0_config.GPIO_PinPuControl = GPIO_PIN_PSEL_DEFAULT;
    GPIO_Init(&io0_config);

    port_is_init_var |= IO0_INIT_MASK;
}

static void io0_write(uint8_t value)
{
    if(!port_is_init(IO0_INIT_MASK)) io0_init();
    GPIO_WriteToOutputPin(PORT1, GPIO_PIN_NO_11, value);
}

static uint8_t io0_read(void)
{
    if(!port_is_init(IO0_INIT_MASK)) io0_init();
    return 0;
    //return GPIO_ReadFromInputPin(PORT1, GPIO_PIN_NO_11);
}

static void io0_toggle(void)
{
    if(!port_is_init(IO0_INIT_MASK)) io0_init();
    GPIO_ToggleOutputPin(PORT1, GPIO_PIN_NO_11);
}

/************************************************************
*                         IO1                               *
*************************************************************/

static void io1_init(void)
{
    GPIO_PinConfig_t io1_config;
    io1_config.pPORT = PORT3;
    io1_config.GPIO_PinNumber = GPIO_PIN_NO_4;
    io1_config.GPIO_PinMode = GPIO_MODE_OUT;
    io1_config.GPIO_PinDrive = GPIO_PIN_DRIVE_LOW;
    io1_config.GPIO_PinOPType = GPIO_PIN_OP_TYPE_CMOS;
    io1_config.GPIO_PinPuControl = GPIO_PIN_PU_DISABLE;
    io1_config.GPIO_PinPuControl = GPIO_PIN_PSEL_DEFAULT;
    GPIO_Init(&io1_config);

    port_is_init_var |= IO1_INIT_MASK;
}

static void io1_write(uint8_t value)
{
    if(!port_is_init(IO1_INIT_MASK)) io1_init();
    GPIO_WriteToOutputPin(PORT3, GPIO_PIN_NO_4, value);
}

static uint8_t io1_read(void)
{
    if(!port_is_init(IO1_INIT_MASK)) io1_init();
    return 0;
    //return GPIO_ReadFromInputPin(PORT1, GPIO_PIN_NO_11);
}

static void io1_toggle(void)
{
    if(!port_is_init(IO1_INIT_MASK)) io1_init();
    GPIO_ToggleOutputPin(PORT3, GPIO_PIN_NO_4);
}

/************************************************************
*                    INSTANCES
*************************************************************/

const IO_Interface_t io0_pin = {
    .init = io0_init,
    .read = io0_read,
    .write = io0_write,
    .toggle = io0_toggle,
    .deinit = NULL
};

const IO_Interface_t io1_pin = {
    .init = io1_init,
    .read = io1_read,
    .write = io1_write,
    .toggle = io1_toggle,
    .deinit = NULL
};

/************************************************************
*                       GET
*************************************************************/

IO_Interface_t *IO_Interface_get(uint8_t pin)
{
    switch (pin)
    {
        case INTERFACE_IO_0: return (IO_Interface_t*)&io0_pin;
        case INTERFACE_IO_1: return (IO_Interface_t*)&io1_pin;
        
        
        default:
            return NULL;
    }
}