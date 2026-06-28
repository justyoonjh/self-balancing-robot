#include "buzz_systick.h"

static volatile uint32_t uwTick = 0;

void SysTick_Init(void)
{
	SYST_CSR = 0;

	SYST_RVR = (SystemCoreClock / 1000) - 1;

	SYST_CVR = 0;

	SYST_CSR = SYST_CSR_CLKSOURCE | SYST_CSR_TICKINT | SYST_CSR_ENABLE;
}

void SysTick_Handler(void)
{
	uwTick++;
}

uint32_t GetTick(void)
{
	return uwTick;
}

void Delay_ms(uint32_t ms)
{
	uint32_t start = GetTick();
	while ((GetTick() - start) < ms);
}
