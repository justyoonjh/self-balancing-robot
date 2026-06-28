#ifndef BUZZ_GPIO_H_
#define BUZZ_GPIO_H_

#include "stm32f446xx.h"

typedef enum {
	GPIO_PIN_NO_0 = 0,
	GPIO_PIN_NO_1,
	GPIO_PIN_NO_2,
	GPIO_PIN_NO_3,
	GPIO_PIN_NO_4,
	GPIO_PIN_NO_5,
	GPIO_PIN_NO_6,
	GPIO_PIN_NO_7,
	GPIO_PIN_NO_8,
	GPIO_PIN_NO_9,
	GPIO_PIN_NO_10,
	GPIO_PIN_NO_11,
	GPIO_PIN_NO_12,
	GPIO_PIN_NO_13,
	GPIO_PIN_NO_14,
	GPIO_PIN_NO_15
}GPIO_PinNumber_t;

typedef enum {
	GPIO_MODE_INPUT = 0,
	GPIO_MODE_OUTPUT = 1,
	GPIO_MODE_ALT = 2,
	GPIO_MODE_ANALOG = 3,
	GPIO_MODE_IT_FT = 4,
	GPIO_MODE_IT_RT = 5,
	GPIO_MODE_IT_RFT = 6
}GPIO_PinMode_t;

typedef enum {
	GPIO_OPTYPE_PP = 0,
	GPIO_OPTYPE_OD = 1
}GPIO_PinOPType_t;

typedef enum {
	GPIO_SPEED_LOW = 0,
	GPIO_SPEED_MEDIUM = 1,
	GPIO_SPEED_FAST = 2,
	GPIO_SPEED_HIGH = 3
}GPIO_PinSpeed_t;

typedef enum {
	GPIO_NO_PUPD = 0,
	GPIO_PU = 1,
	GPIO_PD = 2
}GPIO_PinPuPd_t;

typedef struct
{
	GPIO_PinNumber_t GPIO_PinNumber;
	GPIO_PinMode_t GPIO_PinMode;
	GPIO_PinSpeed_t GPIO_PinSpeed;
	GPIO_PinPuPd_t GPIO_PinPuPdControl;
	GPIO_PinOPType_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;

typedef struct
{
	GPIO_RegMap_t *pGPIOx;
	GPIO_PinConfig_t GPIO_PinConfig;
}GPIO_Handle_t;

void GPIO_PeriClockControl(GPIO_RegMap_t *pGPIOx, uint8_t EnorDi);
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegMap_t *pGPIOx);

uint8_t GPIO_ReadFromInputPin(GPIO_RegMap_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegMap_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegMap_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegMap_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegMap_t *pGPIOx, uint8_t PinNumber);

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t Priority, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);

#endif
