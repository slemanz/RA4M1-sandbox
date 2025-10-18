#include <stdint.h>

#define MMIO32(addr) (*(volatile uint32_t *)(addr))
#define MMIO8(addr)  (*(volatile uint8_t *)(addr))

int main(void)
{
    // config pin
    MMIO8(0x40040D03) |= (1 << 6);
    MMIO32(0x40040020) |= (1 << 11);
    MMIO8(0x40040D03) &= ~(1 << 6);

    while(1)
    {
        MMIO32(0x40040020) ^= (1U << 27);
        for(uint32_t i = 0; i < 20000; i++)
        {
            __asm("NOP");
        }
    }
}