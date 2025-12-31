#include "driver_interrupt.h"

void interrupt_Config(uint8_t IRQNumber, uint8_t EnorDi)
{
    // reference: CORTEX M4 user guide
	if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			// program ISER0 register
			*NVIC_ISER0 |= (1 << IRQNumber);

		}else if(IRQNumber > 31 && IRQNumber < 64) // 32 to 63
		{
			// program ISER1 register
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));

		}else if(IRQNumber >= 64 && IRQNumber < 96) // 64 to 95
		{
			// program ISER2 register
			*NVIC_ISER2 |= (1 << (IRQNumber % 64));

		}
	}else
	{
		if(IRQNumber <= 31)
		{
			// program ICER0 register
			*NVIC_ICER0 |= (1 << IRQNumber);
		}else if(IRQNumber > 31 && IRQNumber < 64)
		{
			// program ICER1 register
			*NVIC_ICER1 |= (1 << (IRQNumber % 32));
		}else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			// program ICER2 register
			*NVIC_ICER2 |= (1 << (IRQNumber % 64));
		}
	}
}

void icu_config(uint8_t event_num, uint32_t event)
{
    ICU->IELSR[event_num] &= ~(0xFF);
    ICU->IELSR[event_num] |=  event;
}

void icu_clear_irq(uint8_t event_num)
{
    uint32_t temp;
    ICU->IELSR[event_num] &= ~(1U << 16);
    temp = ICU->IELSR[event_num];

    (void)temp;
}