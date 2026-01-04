#ifndef INC_DRIVER_SCI_H_
#define INC_DRIVER_SCI_H_

#include "ra4m1.h"

/**
 * @brief Configuration structure for SCIx peripheral
 */
typedef struct
{
    SCI_RegDef_t *pSCIx;
	uint8_t SCI_Mode;
	uint32_t SCI_Baud;
	uint8_t SCI_NoOfStopBits;
	uint8_t SCI_ParityControl;
	// uint8_t SCI_WordLength; // 8 bit only
	// uint8_t SCI_HWFlowControl;
}SCI_Config_t;

/******************************************************************************************
 *              BIT POSITION DEFINITIONS OF SCI PERIPHERAL
 ******************************************************************************************/

#define SCI_SMR_STOP_POS            3
#define SCI_SMR_PM_POS              4
#define SCI_SMR_PE_POS              5

#define SCI_SCR_RE_POS              4
#define SCI_SCR_TE_POS              5
#define SCI_SCR_RIE_POS             6

/******************************************************************************************
 *              BIT MASK DEFINITIONS OF SCI PERIPHERAL
 ******************************************************************************************/

#define SCI_SMR_STOP_MSK            (1U << SCI_SMR_STOP_POS)
#define SCI_SMR_PM_MSK              (1U << SCI_SMR_PM_POS)
#define SCI_SMR_PE_MSK              (1U << SCI_SMR_PE_POS)

#define SCI_SCR_RE_MSK              (1U << SCI_SCR_RE_POS)
#define SCI_SCR_TE_MSK              (1U << SCI_SCR_TE_POS)
#define SCI_SCR_RIE_MSK             (1U << SCI_SCR_RIE_POS)

 /******************************************************************************************
 *                          POSSIBLE CONFIGURATIONS
 ******************************************************************************************/

 /*
 *@SCI_Mode
 *Possible options for SCI_Mode
 */
#define SCI_MODE_ONLY_TX		0
#define SCI_MODE_ONLY_RX		1
#define SCI_MODE_TXRX			2


/*
 *@SCI_Baud
 *Possible options for SCI_Baud
 */
#define SCI_STD_BAUD_1200           1200
#define SCI_STD_BAUD_2400           2400
#define SCI_STD_BAUD_9600           9600
#define SCI_STD_BAUD_19200          19200
#define SCI_STD_BAUD_38400          38400
#define SCI_STD_BAUD_57600          57600
#define SCI_STD_BAUD_115200         115200


/*
 *@SCI_ParityControl
 *Possible options for SCI_ParityControl
 */
#define SCI_PARITY_EN_ODD           2
#define SCI_PARITY_EN_EVEN          1
#define SCI_PARITY_DISABLE          0


/*
 *@SCI_WordLength
 *Possible options for SCI_WordLength
 */
#define SCI_WORDLEN_8BITS           0


/*
 *@SCI_NoOfStopBits
 *Possible options for SCI_NoOfStopBits
 */
#define SCI_STOPBITS_1              0
#define SCI_STOPBITS_2              2

/*
 *@SCI_HWFlowControl
 *Possible options for SCI_HWFlowControl
 */
#define SCI_HW_FLOW_CTRL_NONE           0
#define SCI_HW_FLOW_CTRL_CTS            1
#define SCI_HW_FLOW_CTRL_RTS            2
#define SCI_HW_FLOW_CTRL_CTS_RTS        3


 /******************************************************************************************
 *                          INTERRUPTS
 ******************************************************************************************/

 #define SCI_INTERRUPT_RIE              (SCI_SCR_RIE_MSK)

 /******************************************************************************************
 *                          FLAGS
 ******************************************************************************************/

#define SCI_FLAG_TXE            (1 << SCI_SR_TXE)

 /********************************************************************************************
 * 								APIs supported by this driver
 * 					for more information check the function definitions
 ********************************************************************************************/

/*
 * Init and De-init
 */

void SCI_Init(SCI_Config_t *pSCIConfig);

/*
 * Data write and read
 */

/*
 * Other Peripheral Control APIs
 */

void SCI_StopControl(SCI_RegDef_t *pSCIx, uint8_t EnorDi);
void SCI_BaudConfig(SCI_RegDef_t *pSCIx, uint32_t Baud);
void SCI_InterruptConfig(SCI_RegDef_t *pSCIx, uint8_t register, uint8_t EnorDi);

void sci2_write_byte(uint8_t ch);
void sci2_write(uint8_t* pBuffer, uint32_t Len);

#endif /* INC_DRIVER_SCI_H_ */
