#ifndef INC_RA4M1_H_
#define INC_RA4M1_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define __vo volatile
#define MMIO32(addr) (*(volatile uint32_t *)(addr))
#define MMIO8(addr)  (*(volatile uint8_t *)(addr))

/************************** BASE ADDRESSES **************************/

#define PWPR_BASEADDR               0x40040D03UL
#define PFS_BASEADDR                0x40040800UL

#define PORT0_BASEADDR              0x40040000UL
#define PORT1_BASEADDR              0x40040020UL
#define PORT2_BASEADDR              0x40040040UL

#define SCS_BASE            				(0xE000E000UL)
#define SYSTICK_BASEADDR					(SCS_BASE + 0x0010UL)


/*********************** STRUCTS DEFINITIONS ************************/

typedef struct
{
	__vo uint32_t PCNTR1; 
	__vo uint32_t PCNTR2; 
	__vo uint32_t PCNTR3; 
	__vo uint32_t PCNTR4;  // not available for all ports
}PORT_RegDef_t;

typedef struct
{
  __vo uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __vo uint32_t LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  __vo uint32_t VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  __vo uint32_t CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
}SysTick_RegDef_t;

/*********************** PERIPHERAL DEFINITIONS *********************/

#define PORT0                       ((PORT_RegDef_t*)PORT0_BASEADDR)
#define PORT1                       ((PORT_RegDef_t*)PORT1_BASEADDR)
#define PORT2                       ((PORT_RegDef_t*)PORT2_BASEADDR)

#define SYSTICK         ((SysTick_RegDef_t*)SYSTICK_BASEADDR) 

/************************ IMPORTANT DEFINITIONS *********************/

#define ENABLE                      1
#define DISABLE                     0

#define INTERRUPT_ENABLE()          do{__asm volatile ("MOV R0, #0x0"); __asm volatile("MSR PRIMASK, R0");}while(0)
#define INTERRUPT_DISABLE()         do{__asm volatile ("MOV R0, #0x1"); __asm volatile("MSR PRIMASK, R0");}while(0)

#endif /* INC_RA4M1_H_ */