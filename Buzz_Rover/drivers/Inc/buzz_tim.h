#ifndef BUZZ_TIM_H_
#define BUZZ_TIM_H_

#include "stm32f446xx.h"

void TIM_TimeBase_Init(TIM_RegMap_t *pTIMx, uint16_t psc, uint32_t arr);
void TIM_Start(TIM_RegMap_t *pTIMx);

#endif
