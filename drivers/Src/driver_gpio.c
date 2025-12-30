#include "driver_gpio.h"

static uint32_t gpio_get_pfs(PORT_RegDef_t *pPORTx, uint8_t pin);

void GPIO_PfsweControl(uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        MMIO8(PWPR_BASEADDR) &= ~(GPIO_B0WI_MASK);
        MMIO8(PWPR_BASEADDR) |= GPIO_PFSWE_MASK;
    }else
    {
        MMIO8(PWPR_BASEADDR) &= ~GPIO_PFSWE_MASK;
        MMIO8(PWPR_BASEADDR) |= (GPIO_B0WI_MASK);
    }
}


void GPIO_Init(GPIO_PinConfig_t *pGPIOConfig)
{
    uint32_t temp = 0;
    if(pGPIOConfig->GPIO_PinMode == GPIO_MODE_OUT)
    {
        temp |= (1 << 2);
    }else if(pGPIOConfig->GPIO_PinMode == GPIO_MODE_IN)
    {
        temp &= ~(1 << 2);
    }else if(pGPIOConfig->GPIO_PinMode == GPIO_MODE_ANALOG)
    {
        temp |= (1 << 15);
    }else if(pGPIOConfig->GPIO_PinMode == GPIO_MODE_PSEL)
    {
        temp |= (pGPIOConfig->GPIO_PeriphSel << 24);
        temp |= (1 << 16);
    }

    temp |= (pGPIOConfig->GPIO_PinPuControl << 4);
    temp |= (pGPIOConfig->GPIO_PinOPType << 6);
    temp |= (pGPIOConfig->GPIO_PinDrive << 10);

    uint32_t pfs_addr = gpio_get_pfs(pGPIOConfig->pPORT, pGPIOConfig->GPIO_PinNumber);
    if(pfs_addr == 0) return;

    GPIO_PfsweControl(ENABLE);
    MMIO32(pfs_addr) = temp;
    GPIO_PfsweControl(DISABLE);
}

void GPIO_Init_table(const GPIO_PinConfig_t *pGPIOConfig, uint32_t Len)
{
    if(pGPIOConfig == NULL)
    {
        return;
    }

    for(uint32_t i = 0; i < Len; i++)
    {
        GPIO_Init((GPIO_PinConfig_t*)&pGPIOConfig[i]);
    }


}

void GPIO_WriteToOutputPin(PORT_RegDef_t *pPORTx, uint8_t PinNumber, uint8_t value)
{
    if(value == GPIO_SET)
    {
        pPORTx->PCNTR1 |= (1U << (PinNumber + 16));
    }else
    {
        pPORTx->PCNTR1 &= ~(1U << (PinNumber + 16));
    }
}

void GPIO_ToggleOutputPin(PORT_RegDef_t *pPORTx, uint8_t PinNumber)
{
    pPORTx->PCNTR1 ^= (1U << (PinNumber + 16));
}

static uint32_t gpio_get_pfs(PORT_RegDef_t *pPORTx, uint8_t pin)
{
    if(pPORTx == PORT0)
    {
        return  (PFS_BASEADDR + 4*pin);
    }else if(pPORTx == PORT1)
    {
        return  (PFS_BASEADDR + 0x40 + 4*pin);
    }else if(pPORTx == PORT2)
    {
        return  (PFS_BASEADDR + 0x80 + 4*pin);
    }else if(pPORTx == PORT3)
    {
        return  (PFS_BASEADDR + 0xC0 + 4*pin);
    }else if(pPORTx == PORT4)
    {
        return  (PFS_BASEADDR + 0x100 + 4*pin);
    }

    return 0;
}