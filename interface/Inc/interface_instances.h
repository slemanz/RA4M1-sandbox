#ifndef INC_INTERFACE_INSTANCES_H_
#define INC_INTERFACE_INSTANCES_H_

/************************************************************
*                   COMM INSTANCES                          *
*************************************************************/

#include "interface_comm.h"

extern const Comm_Interface_t sci2_protocol;


/************************************************************
*                     IO INSTANCES                          *
*************************************************************/

#include "interface_io.h"

extern const IO_Interface_t io0_pin;
extern const IO_Interface_t io1_pin;
extern const IO_Interface_t io2_pin;

#endif /* INC_INTERFACE_INSTANCES_H_ */