#include "buzz_gpio.h"

void GPIO_PeriClockControl(GPIO_RegMap_t *pGPIOx, uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
		if (pGPIOx == GPIOA) { GPIOA_CLK(); }
		else if (pGPIOx == GPIOB) { GPIOB_CLK(); }
		else if (pGPIOx == GPIOC) { GPIOC_CLK(); }
		else if (pGPIOx == GPIOD) { GPIOD_CLK(); }
		else if (pGPIOx == GPIOE) { GPIOE_CLK(); }
		else if (pGPIOx == GPIOF) { GPIOF_CLK(); }
		else if (pGPIOx == GPIOG) { GPIOG_CLK(); }
		else if (pGPIOx == GPIOH) { GPIOH_CLK(); }
	}
	else
	{
		if (pGPIOx == GPIOA) { GPIOA_CLK_DI(); }
		else if (pGPIOx == GPIOB) { GPIOB_CLK_DI(); }
		else if (pGPIOx == GPIOC) { GPIOC_CLK_DI(); }
		else if (pGPIOx == GPIOD) { GPIOD_CLK_DI(); }
		else if (pGPIOx == GPIOE) { GPIOE_CLK_DI(); }
		else if (pGPIOx == GPIOF) { GPIOF_CLK_DI(); }
		else if (pGPIOx == GPIOG) { GPIOG_CLK_DI(); }
		else if (pGPIOx == GPIOH) { GPIOH_CLK_DI(); }
	}
}

/*
GPIO_Init 내부 RMW(Read-Modify-Write) 패턴
1. RAM에서 계산(READ)
2. 해당 필드 클리어(MODIFY)
3. 새 값 세팅(WRITE)
*/

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp = 0;
	uint8_t pin = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;

	uint8_t moder_val = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode >= GPIO_MODE_IT_FT)
			? GPIO_MODE_INPUT
			: pGPIOHandle->GPIO_PinConfig.GPIO_PinMode;

	temp = (moder_val << (2 * pin));
	pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pin));
	pGPIOHandle->pGPIOx->MODER |= temp;
	temp = 0;

	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pin));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2 * pin));
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;
	temp = 0;

	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pin));
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2 * pin));
	pGPIOHandle->pGPIOx->PUPDR |= temp;
	temp = 0;

	temp =(pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pin);
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pin);
	pGPIOHandle->pGPIOx->OTYPER |= temp;
	temp = 0;

	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALT)
	{
		uint8_t idx = pin / 8;
		uint8_t offset = pin % 8;
		pGPIOHandle->pGPIOx->AFR[idx] &= ~(0xF << (4 * offset));
		pGPIOHandle->pGPIOx->AFR[idx] |=
				(pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * offset));
	}

	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode >= GPIO_MODE_IT_FT)
	{
		if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			EXTI->FTSR |= (1 << pin);
			EXTI->RTSR &= ~(1 << pin);
		}
		else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			EXTI->RTSR |= (1 << pin);
			EXTI->FTSR &= ~(1 << pin);
		}
		else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			EXTI->FTSR |= (1 << pin);
			EXTI->RTSR |= (1 << pin);
		}

		SYSCFG_CLK();

		uint8_t exticr_idx = pin / 4;
		uint8_t exticr_pos = (pin % 4) * 4;

		uint8_t port_code = 0;
		if (pGPIOHandle->pGPIOx == GPIOA) { port_code = 0; }
		else if (pGPIOHandle->pGPIOx == GPIOB) {port_code = 1;}
		else if (pGPIOHandle->pGPIOx == GPIOC) {port_code = 2;}
		else if (pGPIOHandle->pGPIOx == GPIOD) {port_code = 3;}
		else if (pGPIOHandle->pGPIOx == GPIOE) {port_code = 4;}
		else if (pGPIOHandle->pGPIOx == GPIOF) {port_code = 5;}
		else if (pGPIOHandle->pGPIOx == GPIOG) {port_code = 6;}
		else if (pGPIOHandle->pGPIOx == GPIOH) {port_code = 7;}

		SYSCFG->EXTICR[exticr_idx] &= ~(0xFU << exticr_pos);
		SYSCFG->EXTICR[exticr_idx] |= (port_code << exticr_pos);

		EXTI->IMR |= (1 << pin);
	}
}
void GPIO_DeInit(GPIO_RegMap_t *pGPIOx)
{
	if(pGPIOx == GPIOA) { GPIOA_REG_RESET(); }
	else if(pGPIOx == GPIOB) { GPIOB_REG_RESET(); }
	else if(pGPIOx == GPIOC) { GPIOC_REG_RESET(); }
	else if(pGPIOx == GPIOD) { GPIOD_REG_RESET(); }
	else if(pGPIOx == GPIOE) { GPIOE_REG_RESET(); }
	else if(pGPIOx == GPIOF) { GPIOF_REG_RESET(); }
	else if(pGPIOx == GPIOG) { GPIOG_REG_RESET(); }
	else if(pGPIOx == GPIOH) { GPIOH_REG_RESET(); }
}


uint8_t GPIO_ReadFromInputPin(GPIO_RegMap_t *pGPIOx, uint8_t PinNumber)
{
	return (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x1);
}

uint16_t GPIO_ReadFromInputPort(GPIO_RegMap_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR;
	return value;
}

void GPIO_WriteToOutputPin(GPIO_RegMap_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if (Value == GPIO_PIN_SET)
	{
		pGPIOx->ODR |= (1 << PinNumber);
	}
	else
	{
		pGPIOx->ODR &= ~(1 << PinNumber);
	}
}

void GPIO_WriteToOutputPort(GPIO_RegMap_t *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR = Value;
}

void GPIO_ToggleOutputPin(GPIO_RegMap_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1 << PinNumber);
}

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t Priority, uint8_t EnorDi)
{
	NVIC_IPR(IRQNumber) = (Priority << 4);

	uint8_t iser_idx = IRQNumber / 32;
	uint8_t iser_bit = IRQNumber % 32;

	if (EnorDi == 1)
	{
		NVIC_ISER(iser_idx) |= (1U << iser_bit);
	}
	else
	{
		NVIC_ICER(iser_idx) |= (1U << iser_bit);
	}
}

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
	*((volatile uint32_t*)(NVIC_IPR_BASE + iprx * 4)) |= (IRQPriority << shift_amount);
}

void GPIO_IRQHandling(uint8_t PinNumber)
{
	if (EXTI->PR & (1 << PinNumber))
	{
		EXTI->PR |= (1 << PinNumber);
	}
}
