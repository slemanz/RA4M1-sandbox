#ifndef INC_DRIVER_GPIO_H_
#define INC_DRIVER_GPIO_H_

#include <ra4m1.h>

typedef struct
{
	PORT_RegDef_t *pPORT;      /* hold the base address of the PORT which the pin belongs */
	uint8_t GPIO_PinNumber; 	/*!< possible modes from @GPIO_PIN_NUMBER >*/
	uint8_t GPIO_PinMode;		/*!< possible modes from @GPIO_PIN_MODES >*/
	uint8_t	GPIO_PinDrive; 		/*!< possible modes from @GPIO_PIN_DRIVE >*/
	uint8_t GPIO_PinOPType;		/*!< possible modes from @GPIO_PIN_OP_TYPE >*/
	uint8_t GPIO_PinPuControl;  /*!< possible modes from @GPIO_PIN_PU >*/
	uint8_t GPIO_PeriphSel;	    /*!< possible modes from @GPIO_PIN_PSEL >*/
}GPIO_PinConfig_t;


#define GPIO_SET                ENABLE
#define GPIO_RESET              DISABLE

/*
 * @GPIO_PIN_NUMBER
 * GPIO pin possible number
 */

#define GPIO_PIN_NO_0           0
#define GPIO_PIN_NO_1           1
#define GPIO_PIN_NO_2           2
#define GPIO_PIN_NO_3           3
#define GPIO_PIN_NO_4           4
#define GPIO_PIN_NO_5           5
#define GPIO_PIN_NO_6           6
#define GPIO_PIN_NO_7           7
#define GPIO_PIN_NO_8           8
#define GPIO_PIN_NO_9           9
#define GPIO_PIN_NO_10	        10
#define GPIO_PIN_NO_11	        11
#define GPIO_PIN_NO_12	        12
#define GPIO_PIN_NO_13	        13
#define GPIO_PIN_NO_14	        14
#define GPIO_PIN_NO_15	        15

#define GPIO_PFSWE_OFFSET       6
#define GPIO_PFSWE_MASK         (1U << GPIO_PFSWE_OFFSET)

/*
 * @GPIO_PIN_MODE
 * GPIO pin possible modes
 */

#define GPIO_MODE_IN        0
#define GPIO_MODE_OUT       1
#define GPIO_MODE_PSEL      2
#define GPIO_MODE_ANALOG    3

/*
 * @GPIO_PIN_DRIVE
 * GPIO pin possible modes
 */

#define GPIO_PIN_DRIVE_LOW      0
#define GPIO_PIN_DRIVE_MIDLE    1

/*
 * @GPIO_PIN_OP_TYPE
 * GPIO pin possible modes
 */

#define GPIO_PIN_OP_TYPE_CMOS   1
#define GPIO_PIN_OP_TYPE_NMOS   1   // open-drain

/*
 * @GPIO_PIN_PUPD
 * GPIO pin possible modes
 */

#define GPIO_PIN_PU_DISABLE     0     
#define GPIO_PIN_PU_ENABLE      1

/*
 * @GPIO_PIN_PSEL
 * GPIO pin possible modes
 */

 #define GPIO_PIN_PSEL_DEFAULT      0


/********************************************************************************************
 * 								APIs supported by this driver
 * 					for more information check the function definitions
 ********************************************************************************************/
void GPIO_PfsweControl(uint8_t EnorDi);

/*
 * Init and De-init
 */
void GPIO_Init(GPIO_PinConfig_t *pGPIOConfig);
void GPIO_Init_table(const GPIO_PinConfig_t *pGPIOConfig, uint32_t Len);

void GPIO_DeInit(void); // not implemented

/*
 * Data read and write
 */

//uint8_t GPIO_ReadFromInputPin(PORT_RegDef_t *pGPIOx, uint8_t PinNumber);
void    GPIO_WriteToOutputPin(PORT_RegDef_t *pPORTx, uint8_t PinNumber, uint8_t value);
void    GPIO_ToggleOutputPin(PORT_RegDef_t *pPORTx, uint8_t PinNumber);

#endif /* INC_DRIVER_GPIO_H_ */