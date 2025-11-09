#ifndef INC_RA4M1_H_
#define INC_RA4M1_H_

#include <stdint.h>
#include <stdbool.h>

#define __vo volatile
#define MMIO32(addr) (*(volatile uint32_t *)(addr))
#define MMIO8(addr)  (*(volatile uint8_t *)(addr))

/************************** BASE ADDRESSES **************************/

#define PWPR_BASEADDR               0x40040D03UL
#define PFS_BASEADDR                0x40040800UL

#define PORT0_BASEADDR              0x40040000UL
#define PORT1_BASEADDR              0x40040020UL
#define PORT2_BASEADDR              0x40040040UL


/*********************** STRUCTS DEFINITIONS ************************/

typedef struct
{
	__vo uint32_t PCNTR1; 
	__vo uint32_t PCNTR2; 
	__vo uint32_t PCNTR3; 
	__vo uint32_t PCNTR4;  // not available for all ports
}PORT_RegDef_t;

/*********************** PERIPHERAL DEFINITIONS *********************/

#define PORT0                       ((PORT_RegDef_t*)PORT0_BASEADDR)
#define PORT1                       ((PORT_RegDef_t*)PORT1_BASEADDR)
#define PORT2                       ((PORT_RegDef_t*)PORT2_BASEADDR)


/************************ IMPORTANT DEFINITIONS *********************/

#define ENABLE                      1
#define DISABLE                     0

#endif /* INC_RA4M1_H_ */