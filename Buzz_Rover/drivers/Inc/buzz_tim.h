#ifndef BUZZ_TIM_H_
#define BUZZ_TIM_H_

#include "stm32f446xx.h"

typedef struct
{
	uint8_t TIM_Channel;
	uint16_t TIM_Prescaler;
	uint16_t TIM_Period;
	uint8_t TIM_OCPreload;
}TIM_Config_t;

typedef struct
{
	TIM_RegMap_t *pTIMx;
	TIM_Config_t TIM_Config;
}TIM_Handle_t;

typedef struct
{
	uint32_t overflow_count;
	uint32_t cnt;
}TIM_Timestamp_t;

uint32_t TIM_GetOverflowCount(void);
TIM_Timestamp_t TIM_GetTimestamp(TIM_RegMap_t *pTIMx);
uint32_t TIM_GetElapsedUS_Long(TIM_RegMap_t *pTIMx, TIM_Timestamp_t start);

void TIM_TimeBase_Init(TIM_RegMap_t *pTIMx, uint16_t psc, uint32_t arr);
void TIM_Start(TIM_RegMap_t *pTIMx);

uint32_t TIM_GetElapsedUs(TIM_RegMap_t *pTIMx, uint32_t start_cnt);

void TIM_PWM_Init(TIM_Handle_t *pTIMHandle);

#endif
