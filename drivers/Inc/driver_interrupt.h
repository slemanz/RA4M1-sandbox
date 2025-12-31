#ifndef INC_DRIVER_INTERRUPT_H_
#define INC_DRIVER_INTERRUPT_H_

#include "ra4m1.h"

#define IRQ_NO_0                0

#define ICU_EVENT_NO_0          0
#define ICU_EVENT_NO_1          1
#define ICU_EVENT_NO_2          2
#define ICU_EVENT_NO_3          3
#define ICU_EVENT_NO_4          4
#define ICU_EVENT_NO_5          5
#define ICU_EVENT_NO_6          6
#define ICU_EVENT_NO_7          7
#define ICU_EVENT_NO_8          8

#define ICU_EVENT_SCI2_RXI      0xA3U

/********************************************************************************************
 *                              APIs supported by this driver                               *
 *                  for more information check the function definitions                     *
 ********************************************************************************************/

void interrupt_Config(uint8_t IRQNumber, uint8_t EnorDi);
void icu_config(uint8_t event_num, uint32_t event);
void icu_clear_irq(uint8_t event_num);


#endif /* INC_DRIVER_INTERRUPT_H_ */