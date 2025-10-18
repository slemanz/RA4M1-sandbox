#include <stdint.h>

#define SRAM_START      0x20000000U
#define SRAM_SIZE       (32 * 1024) // 128K bytes
#define SRAM_END        ((SRAM_START) + (SRAM_SIZE))

#define STACK_START     (SRAM_END)

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _la_data;

extern uint32_t _sbss;
extern uint32_t _ebss;


/* Prototype of main*/
int main(void);

void __libc_init_array(void);



/* Functions prototypes of STM32F401 system exceptions and IRQ handlers */
void Reset_Handler(void);


void NMI_Handler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler              (void) __attribute__ ((weak, alias("Default_Handler"))); 
void MemManage_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler               (void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler               (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler                (void) __attribute__ ((weak, alias("Default_Handler")));

__attribute__((section(".isr_vector")))
uint32_t vectors[256]  = {
    STACK_START,                    // 0
    (uint32_t)Reset_Handler,        // 1
    (uint32_t)NMI_Handler,          // 2
    (uint32_t)HardFault_Handler,    // 3
    (uint32_t)MemManage_Handler,    // 4
    (uint32_t)BusFault_Handler,     // 5
    (uint32_t)UsageFault_Handler,   // 6
    0,
    0,
    0,
    0,
    (uint32_t)SVC_Handler,
    (uint32_t)DebugMon_Handler,
    0,
    (uint32_t)PendSV_Handler,
    (uint32_t)SysTick_Handler,
    0,                              // 17
    0,                              // 18
    0,                              // 19
    0,                              // 20
    0,                              // 21
    0,                              // 22
    0,                              // 23
    0,                              // 24
    0,                              // 25
    0,                              // 26
    0,                              // 27
    0,                              // 28
    0,                              // 29
    0,                              // 30
    0,                              // 31
    0,                              // 32
    0,                              // 33
    0,                              // 34
    0,                              // 35
    0,                              // 36
    0,                              // 37
    0,                              // 38
    0,                              // 39
    0,                              // 40
    0,                              // 41
    0,                              // 42
    0,                              // 43
    0,                              // 44
    0,                              // 45
    0,                              // 46
    0,                              // 47
    0,                              // 48
    0,                              // 49
    0,                              // 50
    0,                              // 51
    0,                              // 52
    0,                              // 53
    0,                              // 54
    0,                              // 55
    0,                              // 56
    0,                              // 57
    0,                              // 58
};

__attribute__((section(".flash_config")))
uint32_t configs[16]  = {
    0xFFFFFFFF,
    0xFFFFCEDF,
    0x00FFFFFC, // 1
    0x00FFFFFF, // 2
    0x00FFFFFC, // 3
    0x00FFFFFF, // 4
    0x00FFFFFC, // 5
    0x00FFFFFF, // 6
    0x200FFFFC, // 7
    0x200FFFFF, // 8
    0x407FFFFC, // 9
    0x407FFFFF, // 10
    0x400DFFFC, // 11
    0x400DFFFF, // 12
    0xFFFFFFFF, // 13
    0xFFFFFFFF  // dont need
};

void Default_Handler(void)
{
    while(1);
}

void Reset_Handler(void)
{
    // copy .data section to SRAM
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;

    uint8_t *pDst = (uint8_t*)&_sdata; //sram
    uint8_t *pSrc = (uint8_t*)&_la_data; //flash

    for(uint32_t i = 0; i < size; i++)
    {
        *pDst++ = *pSrc++;
    }

    // Init the .bss section to zero in SRAM
    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pDst = (uint8_t*)&_sbss;

    for(uint32_t i = 0; i < size; i++)
    {
        *pDst++ = 0;
    }


    // call init function of std. library
    __libc_init_array();

    // call main()
    __asm volatile("MSR MSP, %0": : "r" (STACK_START): ); // stack reset
    main();
}
