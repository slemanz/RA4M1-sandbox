#include "interface/interface.h"
#include "interface_instances.h"
#include "interface_defines.h"


Comm_Interface_t *Comm_ProtocolGet(uint8_t type)
{
    switch (type)
    {
        case INTERFACE_PROTOCOL_SCI2: return (Comm_Interface_t*)&sci2_protocol;
        default: return NULL;
    }
}