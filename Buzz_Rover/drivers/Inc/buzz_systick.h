#ifndef BUZZ_SYSTICK_H_
#define BUZZ_SYSTICK_H_

#include <stdint.h>

#define SYSTICK_BASE				0xE000E010UL

#define SYST_CSR (*((volatile uint32_t*)(SYSTICK_BASE + 0x00)))
#define SYST_RVR (*((volatile uint32_t*)(SYSTICK_BASE + 0x04)))
#define SYST_CVR (*((volatile uint32_t*)(SYSTICK_BASE + 0x08)))

#define SYST_CSR_ENABLE ( 1 << 0 )
#define SYST_CSR_TICKINT ( 1 << 1 )
#define SYST_CSR_CLKSOURCE ( 1 << 2 )
#define SYST_CSR_COUNTFLAG ( 1 << 16 )

extern uint32_t SystemCoreClock;

void SysTick_Init(void);
void Delay_ms(uint32_t ms);
uint32_t GetTick(void);

#endif
