#include "driver_sci.h"
#include "driver_clock.h"

static uint8_t calculate_brr(uint32_t baud, uint32_t clock);

static uint8_t calculate_brr(uint32_t baud, uint32_t clock)
{
    uint32_t calc = (clock)/(32*baud) - 1;
    return (uint8_t)calc;
}

void SCI_StopControl(SCI_RegDef_t *pSCIx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pSCIx == SCI2)
        {
            SCI2_STOP_EN();
        }
    }else
    {
        if(pSCIx == SCI2)
        {
            SCI2_STOP_DI();
        }
    }
}

void SCI_BaudConfig(SCI_RegDef_t *pSCIx, uint32_t Baud)
{
    pSCIx->BRR = calculate_brr(Baud, clock_system_get());
    for(uint32_t i = 0; i < 100; i++);
}

uint8_t SCI_GetFlagStatus(SCI_RegDef_t *pSCIx, uint8_t flagName)
{
    if(pSCIx->SSR & flagName)
    {
        return FLAG_SET;
    }
    return FLAG_RESET;
}

void SCI_Init(SCI_Config_t *pSCIConfig)
{
    SCI_StopControl(pSCIConfig->pSCIx, DISABLE);
    SCI_BaudConfig(pSCIConfig->pSCIx, pSCIConfig->SCI_Baud);

    uint8_t temp = 0;
    if(pSCIConfig->SCI_NoOfStopBits == SCI_STOPBITS_2) temp |= (SCI_SMR_STOP_MSK);

    if(pSCIConfig->SCI_ParityControl == SCI_PARITY_EN_EVEN)
    {
        temp |= (SCI_SMR_PE_MSK);
    }else if(pSCIConfig->SCI_ParityControl == SCI_PARITY_EN_ODD)
    {
        temp |= (SCI_SMR_PE_MSK | SCI_SMR_PM_MSK);
    }
    pSCIConfig->pSCIx->SMR = temp;

    temp = 0;
    if(pSCIConfig->SCI_Mode == SCI_MODE_ONLY_TX)
    {
        temp |= SCI_SCR_RE_MSK;
    }else if(pSCIConfig->SCI_Mode == SCI_MODE_ONLY_RX)
    {
        temp |= SCI_SCR_TE_MSK;
    }else if(pSCIConfig->SCI_Mode == SCI_MODE_TXRX)
    {
        temp |= (SCI_SCR_RE_MSK | SCI_SCR_TE_MSK);
    }
    pSCIConfig->pSCIx->SCR = temp;
}

void SCI_InterruptConfig(SCI_RegDef_t *pSCIx, uint8_t regs, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        pSCIx->SCR |= regs;
    }else if(EnorDi == DISABLE)
    {
        pSCIx->SCR &= ~(regs);
    }
}

void SCI_WriteByte(SCI_RegDef_t *pSCIx, uint8_t *pTxBuffer)
{
    pSCIx->TDR = *pTxBuffer;
}

void SCI_Write(SCI_RegDef_t *pSCIx, uint8_t *pTxBuffer, uint32_t Len)
{
    for(uint32_t i = 0; i < Len; i++)
    {
        while(!SCI_GetFlagStatus(pSCIx, SCI_FLAG_TDRE)); // wait transmit
        SCI_WriteByte(pSCIx, pTxBuffer);
        pTxBuffer++;
    }
    while(!SCI_GetFlagStatus(pSCIx, SCI_FLAG_TEND)); // wait complete

}

void SCI_ReadByte(SCI_RegDef_t *pSCIx, uint8_t *pRxBuffer)
{
    *pRxBuffer = pSCIx->RDR;
}