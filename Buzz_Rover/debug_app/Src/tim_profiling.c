#include "tim_profiling.h"
#include "buzz_tim.h"
#include "buzz_systick.h"
#include "stm32f446xx_tim.h"
#include <stdio.h>

void TIM_ProfileTest_Run(void)
{
	uint32_t tim_start = TIM2->CNT;
	for(volatile int i = 0; i < 1300; i++);
	uint32_t elapsed_us = TIM_GetElapsedUs(TIM2, tim_start);

	uint32_t tick_start = GetTick();
	for(volatile int i = 0; i < 1000; i++);
	uint32_t elapsed_ms = GetTick() - tick_start;

	printf("CNT elapsed: %lu us / GetTick elapsed: %lu ms\r\n", elapsed_us, elapsed_ms);
	printf("UIF Flag: %lu\r\n", (TIM2->SR & ( 1 << 0)));
}
