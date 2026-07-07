#include "buzz_tim.h"

void TIM_TimeBase_Init(TIM_RegMap_t *pTIMx, uint16_t psc, uint32_t arr)
{
	pTIMx->PSC = psc;
	pTIMx->ARR = arr;

	pTIMx->EGR |= (1 << 0);
}

void TIM_Start(TIM_RegMap_t *pTIMx)
{
	pTIMx->CR1 |= (1 << 0);
}
