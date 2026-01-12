#include "interface_io.h"
#include "interface_instances.h"

IO_Interface_t *IO_Interface_get(IO_Pin_e pin)
{
    switch (pin)
    {
        case IO0: return (IO_Interface_t*)&io0_pin;
        case IO1: return (IO_Interface_t*)&io1_pin;
        
        
        default:
            return NULL;
    }
}