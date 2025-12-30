#include "driver_sci.h"
#include "driver_clock.h"

static uint8_t calculate_brr(uint32_t baud, uint32_t clock);

static uint8_t calculate_brr(uint32_t baud, uint32_t clock)
{
    uint32_t calc = (clock)/(32*baud) - 1;
    return (uint8_t)calc;
}

void sci2_init(void)
{
    // clear stop mode SCI2
    MSTPCRB &= ~(1 << 29);

    // set baudrate
    SCI2->BRR = calculate_brr(115200, clock_system_get());
    for(uint32_t i = 0; i < 100; i++);

    // transmit enable
    SCI2->SCR |= (1 << 5);
}

void sci2_write_byte(uint8_t ch)
{
    while(!(SCI2->SSR & (1 << 7))); // wait transmit
    SCI2->TDR = ch;
    SCI2->SSR &= ~(1 << 7); // clear flag
    while(!(SCI2->SSR & (1 << 7))); // wait transmit

    //while(!(SCI2->SSR & (1 << 2))); // wait transmit complete
}