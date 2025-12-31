#ifndef INC_RA4M1_H_
#define INC_RA4M1_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define __vo volatile
#define MMIO32(addr) (*(volatile uint32_t *)(addr))
#define MMIO16(addr)  (*(volatile uint16_t *)(addr))
#define MMIO8(addr)  (*(volatile uint8_t *)(addr))

/*******************START: Processor Specific Details *************************/
/*
 * 	ARM-Cortex Mx Processor NVIC ISERx register addresses
 */

#define NVIC_ISER0 						((__vo uint32_t*)0xE000E100UL)
#define NVIC_ISER1 						((__vo uint32_t*)0xE000E104UL)
#define NVIC_ISER2 						((__vo uint32_t*)0xE000E108UL)
#define NVIC_ISER3 						((__vo uint32_t*)0xE000E10CUL)

/*
 * 	ARM-Cortex Mx Processor NVIC ISERx register addresses
 */

#define NVIC_ICER0 						((__vo uint32_t*)0xE000E180UL)
#define NVIC_ICER1 						((__vo uint32_t*)0xE000E184UL)
#define NVIC_ICER2 						((__vo uint32_t*)0xE000E188UL)
#define NVIC_ICER3 						((__vo uint32_t*)0xE000E18CUL)

/************************** BASE ADDRESSES **************************/



#define PWPR_BASEADDR               0x40040D03UL
#define PFS_BASEADDR                0x40040800UL

// module stop
#define MSTPCRB_BASEADDR            0x40047000UL

#define PORT0_BASEADDR              0x40040000UL
#define PORT1_BASEADDR              0x40040020UL
#define PORT2_BASEADDR              0x40040040UL
#define PORT3_BASEADDR              0x40040060UL
#define PORT4_BASEADDR              0x40040080UL
#define PORT5_BASEADDR              0x400400A0UL
#define PORT6_BASEADDR              0x400400C0UL
#define PORT7_BASEADDR              0x400400E0UL
#define PORT8_BASEADDR              0x40040100UL
#define PORT9_BASEADDR              0x40040120UL

#define SCS_BASE            				(0xE000E000UL)
#define SYSTICK_BASEADDR					(SCS_BASE + 0x0010UL)

#define SCI0_BASEADDR               0x40070000UL
#define SCI1_BASEADDR               0x40070020UL
#define SCI2_BASEADDR               0x40070040UL
#define SCI9_BASEADDR               0x40070120UL

#define ICU_BASEADDR                0x40006000UL

/************************** REG ADDRESSES ***************************/

// Write Protection
#define REG_PRCR_ADDRESS            0x4001E3FEUL

// Clock
#define REG_SCKDIVCR_ADDRESS        0x4001E020UL
#define REG_SCKSCR_ADDRESS          0x4001E026UL
#define REG_MEMWAIT_ADDRESS         0x4001E031UL
#define REG_HOCOCR_ADDRESS          0x4001E036UL

/*********************** OFFSET DEFINITIONS *************************/

#define SCKDIVCR_FCK_OFFSET         28
#define SCKDIVCR_ICK_OFFSET         24
#define SCKDIVCR_PCKA_OFFSET        12
#define SCKDIVCR_PCKB_OFFSET        8
#define SCKDIVCR_PCKC_OFFSET        4
#define SCKDIVCR_PCKD_OFFSET        0

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
    union
    {
        __vo uint8_t SMR;               /*!< (@ 0x00000000) Serial Mode Register (SCMR.SMIF = 0)                       */
        __vo uint8_t SMR_SMCI;          /*!< (@ 0x00000000) Serial mode register (SCMR.SMIF = 1)                       */
    };

    __vo uint8_t BRR;                   /*!< (@ 0x00000001) Bit Rate Register                                          */

    union
    {
        __vo uint8_t SCR;               /*!< (@ 0x00000002) Serial Control Register (SCMR.SMIF = 0)                    */
        __vo uint8_t SCR_SMCI;          /*!< (@ 0x00000002) Serial Control Register (SCMR.SMIF =1)                     */
    };

    __vo uint8_t TDR;                   /*!< (@ 0x00000003) Transmit Data Register                                     */

    union
    {
        __vo uint8_t SSR;               /*!< (@ 0x00000004) Serial Status Register(SCMR.SMIF = 0 and FCR.FM=0)         */
        __vo uint8_t SSR_FIFO;          /*!< (@ 0x00000004) Serial Status Register(SCMR.SMIF = 0 and FCR.FM=1)         */
        __vo uint8_t SSR_MANC;          /*!< (@ 0x00000004) Serial Status Register for Manchester Mode (SCMR.SMIF */
        __vo uint8_t SSR_SMCI;          /*!< (@ 0x00000004) Serial Status Register(SCMR.SMIF = 1)                      */
    };

    __vo uint8_t RDR;                   /*!< (@ 0x00000005) Receive Data Register                                      */
    __vo uint8_t SCMR;                  /*!< (@ 0x00000006) Smart Card Mode Register                                   */
    __vo uint8_t SEMR;                  /*!< (@ 0x00000007) Serial Extended Mode Register                              */
    __vo uint8_t SNFR;                  /*!< (@ 0x00000008) Noise Filter Setting Register                              */
    __vo uint8_t SIMR1;                 /*!< (@ 0x00000009) I2C Mode Register 1                                        */
    __vo uint8_t SIMR2;                 /*!< (@ 0x0000000A) I2C Mode Register 2                                        */
    __vo uint8_t SIMR3;                 /*!< (@ 0x0000000B) I2C Mode Register 3                                        */
    __vo uint8_t SISR;                  /*!< (@ 0x0000000C) I2C Status Register                                        */
    __vo uint8_t SPMR;                  /*!< (@ 0x0000000D) SPI Mode Register                                          */

    union
    {
        __vo uint16_t TDRHL;            /*!< (@ 0x0000000E) Transmit 9-bit Data Register                               */
        __vo uint16_t FTDRHL;           /*!< (@ 0x0000000E) Transmit FIFO Data Register HL                             */
        __vo uint16_t TDRHL_MAN;        /*!< (@ 0x0000000E) Transmit Data Register for Manchester Mode (MMR.MANEN      */

        struct
        {
            __vo uint8_t FTDRH;         /*!< (@ 0x0000000E) Transmit FIFO Data Register H                              */
            __vo uint8_t FTDRL;         /*!< (@ 0x0000000F) Transmit FIFO Data Register L                              */
        };
    };

    union
    {
        __vo uint16_t RDRHL;            /*!< (@ 0x00000010) Receive 9-bit Data Register                                */
        __vo uint16_t FRDRHL;           /*!< (@ 0x00000010) Receive FIFO Data Register HL                              */
        __vo uint16_t RDRHL_MAN;        /*!< (@ 0x00000010) Receive Data Register for Manchester Mode (MMR.MANEN       */

        struct
        {
            __vo uint8_t FRDRH;         /*!< (@ 0x00000010) Receive FIFO Data Register H                               */
            __vo uint8_t FRDRL;         /*!< (@ 0x00000011) Receive FIFO Data Register L                               */
        };
    };

    __vo uint8_t MDDR;                  /*!< (@ 0x00000012) Modulation Duty Register                                   */
    __vo uint8_t DCCR;                  /*!< (@ 0x00000013) Data Compare Match Control Register                        */
    __vo uint16_t FCR;                  /*!< (@ 0x00000014) FIFO Control Register                                      */
    __vo uint16_t FDR;                  /*!< (@ 0x00000016) FIFO Data Count Register                                   */
    __vo uint16_t LSR;                  /*!< (@ 0x00000018) Line Status Register                                       */
    __vo uint16_t CDR;                  /*!< (@ 0x0000001A) Compare Match Data Register                                */
    __vo uint8_t SPTR;                  /*!< (@ 0x0000001C) Serial Port Register                                       */
    __vo uint8_t ACTR;                  /*!< (@ 0x0000001D) Adjustment Communication Timing Register                   */
    __vo uint16_t RESERVED;

    union
    {
        __vo uint8_t ESMER;             /*!< (@ 0x00000020) Extended Serial Module Enable Register                     */
        __vo uint8_t MMR;               /*!< (@ 0x00000020) Manchester Mode Register                                   */
    };

    __vo uint8_t CR0;                   /*!< (@ 0x00000021) Control Register 0                                         */

    union
    {
        __vo uint8_t CR1;               /*!< (@ 0x00000022) Control Register 1                                         */
        __vo uint8_t TMPR;              /*!< (@ 0x00000022) Transmit Manchester Preface Setting Register               */
    };

    union
    {
        __vo uint8_t CR2;               /*!< (@ 0x00000023) Control Register 2                                         */
        __vo uint8_t RMPR;              /*!< (@ 0x00000023) Receive Manchester Preface Setting Register                */
    };

    union
    {
        __vo uint8_t CR3;               /*!< (@ 0x00000024) Control Register 3                                         */
        __vo uint8_t MESR;              /*!< (@ 0x00000024) Manchester Extended Error Status Register                  */
    };

    union
    {
        __vo uint8_t PCR;               /*!< (@ 0x00000025) Port Control Register                                      */
        __vo uint8_t MECR;              /*!< (@ 0x00000025) Manchester Extended Error Control Register                 */
    };

    __vo uint8_t ICR;                   /*!< (@ 0x00000026) Interrupt Control Register                                 */
    __vo uint8_t STR;                   /*!< (@ 0x00000027) Status Register                                            */
    __vo uint8_t STCR;                  /*!< (@ 0x00000028) Status Clear Register                                      */
    __vo uint8_t CF0DR;                 /*!< (@ 0x00000029) Control Field 0 Data Register                              */
    __vo uint8_t CF0CR;                 /*!< (@ 0x0000002A) Control Field 0 Compare Enable Register                    */
    __vo uint8_t CF0RR;                 /*!< (@ 0x0000002B) Control Field 0 Receive Data Register                      */
    __vo uint8_t PCF1DR;                /*!< (@ 0x0000002C) Primary Control Field 1 Data Register                      */
    __vo uint8_t SCF1DR;                /*!< (@ 0x0000002D) Secondary Control Field 1 Data Register                    */
    __vo uint8_t CF1CR;                 /*!< (@ 0x0000002E) Control Field 1 Compare Enable Register                    */
    __vo uint8_t CF1RR;                 /*!< (@ 0x0000002F) Control Field 1 Receive Data Register                      */
    __vo uint8_t TCR;                   /*!< (@ 0x00000030) Timer Control Register                                     */
    __vo uint8_t TMR;                   /*!< (@ 0x00000031) Timer Mode Register                                        */
    __vo uint8_t TPRE;                  /*!< (@ 0x00000032) Timer Prescaler Register                                   */
    __vo uint8_t TCNT;                  /*!< (@ 0x00000033) Timer Count Register                                       */
    __vo uint16_t RESERVED1[4];
    __vo uint8_t SCIMSKEN;              /*!< (@ 0x0000003C) SCI5 TXD Output Mask Enable Register                       */
    __vo uint8_t  RESERVED2;
    __vo uint16_t RESERVED3;
}SCI_RegDef_t;                         /*!< Size = 64 (0x40)  */


typedef struct                         
{
    __vo uint8_t IRQCR[16];             /*!< (@ 0x00000000) IRQ Control Register [0..15]                               */
    __vo uint32_t RESERVED[60];
    __vo uint8_t NMICR;                 /*!< (@ 0x00000100) NMI Pin Interrupt Control Register                         */
    __vo uint8_t  RESERVED1;
    __vo uint16_t RESERVED2;
    __vo uint32_t RESERVED3[7];
    __vo uint16_t NMIER;                /*!< (@ 0x00000120) Non-Maskable Interrupt Enable Register                     */
    __vo uint16_t RESERVED4;
    __vo uint32_t RESERVED5[3];
    __vo uint16_t NMICLR;               /*!< (@ 0x00000130) Non-Maskable Interrupt Status Clear Register               */
    __vo uint16_t RESERVED6;
    __vo uint32_t RESERVED7[3];
    __vo uint16_t NMISR;                /*!< (@ 0x00000140) Non-Maskable Interrupt Status Register                     */
    __vo uint16_t RESERVED8;
    __vo uint32_t RESERVED9[23];
    __vo uint32_t WUPEN;                /*!< (@ 0x000001A0) Wake Up Interrupt Enable Register                          */
    __vo uint32_t WUPEN1;               /*!< (@ 0x000001A4) Wake Up interrupt enable register 1                        */
    __vo uint32_t WUPEN2;               /*!< (@ 0x000001A8) Wake Up Interrupt Enable Register 2                        */
    __vo uint32_t RESERVED10[5];
    __vo uint8_t IELEN;                 /*!< (@ 0x000001C0) ICU event Enable Register                                  */
    __vo uint8_t  RESERVED11;
    __vo uint16_t RESERVED12;
    __vo uint32_t RESERVED13[15];
    __vo uint16_t SELSR0;               /*!< (@ 0x00000200) Snooze Event Link Setting Register                         */
    __vo uint16_t RESERVED14;
    __vo uint32_t RESERVED15[31];
    __vo uint32_t DELSR[8];             /*!< (@ 0x00000280) DMAC Event Link Setting Register                           */
    __vo uint32_t RESERVED16[24];
    __vo uint32_t IELSR[96];            /*!< (@ 0x00000300) ICU Event Link Setting Register [0..95]                    */
}ICU_RegDef_t; 

typedef struct
{
  __vo uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __vo uint32_t LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  __vo uint32_t VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  __vo uint32_t CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
}SysTick_RegDef_t;

/*********************** PERIPHERAL DEFINITIONS *********************/

#define MSTPCRB                     (*((__vo uint32_t*)MSTPCRB_BASEADDR))

#define PORT0                       ((PORT_RegDef_t*)PORT0_BASEADDR)
#define PORT1                       ((PORT_RegDef_t*)PORT1_BASEADDR)
#define PORT2                       ((PORT_RegDef_t*)PORT2_BASEADDR)
#define PORT3                       ((PORT_RegDef_t*)PORT3_BASEADDR)
#define PORT4                       ((PORT_RegDef_t*)PORT4_BASEADDR)
#define PORT5                       ((PORT_RegDef_t*)PORT5_BASEADDR)
#define PORT6                       ((PORT_RegDef_t*)PORT6_BASEADDR)
#define PORT7                       ((PORT_RegDef_t*)PORT7_BASEADDR)
#define PORT8                       ((PORT_RegDef_t*)PORT8_BASEADDR)
#define PORT9                       ((PORT_RegDef_t*)PORT9_BASEADDR)

#define SYSTICK                     ((SysTick_RegDef_t*)SYSTICK_BASEADDR) 

#define SCI0                        ((SCI_RegDef_t*)SCI0_BASEADDR)
#define SCI1                        ((SCI_RegDef_t*)SCI1_BASEADDR)
#define SCI2                        ((SCI_RegDef_t*)SCI2_BASEADDR)
#define SCI9                        ((SCI_RegDef_t*)SCI9_BASEADDR)

#define ICU                         ((ICU_RegDef_t*)ICU_BASEADDR)

/************************ IMPORTANT DEFINITIONS *********************/

#define ENABLE                      1
#define DISABLE                     0

#define INTERRUPT_ENABLE()          do{__asm volatile ("MOV R0, #0x0"); __asm volatile("MSR PRIMASK, R0");}while(0)
#define INTERRUPT_DISABLE()         do{__asm volatile ("MOV R0, #0x1"); __asm volatile("MSR PRIMASK, R0");}while(0)

#define PRCR_KEY_CODE               0xA500

#endif /* INC_RA4M1_H_ */