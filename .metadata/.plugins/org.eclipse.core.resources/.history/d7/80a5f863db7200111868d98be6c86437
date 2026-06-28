#ifndef STM32F446XX_GPIO_H_
#define STM32F446XX_GPIO_H_

#include <stdint.h>

#define GPIOA_BASEADDR 	(AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASEADDR 	(AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASEADDR 	(AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASEADDR 	(AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASEADDR 	(AHB1PERIPH_BASE + 0x1000)
#define GPIOF_BASEADDR 	(AHB1PERIPH_BASE + 0x1400)
#define GPIOG_BASEADDR 	(AHB1PERIPH_BASE + 0x1800)
#define GPIOH_BASEADDR 	(AHB1PERIPH_BASE + 0x1C00)

#define SYSCFG_BASEADDR		(APB2PERIPH_BASE + 0x3800)
#define EXTI_BASEADDR		(APB2PERIPH_BASE + 0x3C00)

typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];
}GPIO_RegMap_t;

typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_RegMap_t;

typedef struct
{
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR[4];
	volatile uint32_t RESERVED[2];
	volatile uint32_t CMPCR;
	volatile uint32_t RESERVED2[2];
	volatile uint32_t CFGR;
}SYSCFG_RegMap_t;

#define GPIOA				((GPIO_RegMap_t*) GPIOA_BASEADDR)
#define GPIOB				((GPIO_RegMap_t*) GPIOB_BASEADDR)
#define GPIOC				((GPIO_RegMap_t*) GPIOC_BASEADDR)
#define GPIOD				((GPIO_RegMap_t*) GPIOD_BASEADDR)
#define GPIOE				((GPIO_RegMap_t*) GPIOE_BASEADDR)
#define GPIOF				((GPIO_RegMap_t*) GPIOF_BASEADDR)
#define GPIOG				((GPIO_RegMap_t*) GPIOG_BASEADDR)
#define GPIOH				((GPIO_RegMap_t*) GPIOH_BASEADDR)

#define EXTI				((EXTI_RegMap_t*) EXTI_BASEADDR)
#define SYSCFG			((SYSCFG_RegMap_t*) SYSCFG_BASEADDR)

#define GPIOA_CLK()		(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_CLK()		(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_CLK()		(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_CLK()		(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_CLK()		(RCC->AHB1ENR |= (1 << 4))
#define GPIOF_CLK()		(RCC->AHB1ENR |= (1 << 5))
#define GPIOG_CLK()		(RCC->AHB1ENR |= (1 << 6))
#define GPIOH_CLK()		(RCC->AHB1ENR |= (1 << 7))

#define SYSCFG_CLK()		(RCC->APB2ENR |= (1 << 14))

#define GPIOA_CLK_DI()		(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_CLK_DI()		(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_CLK_DI()		(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_CLK_DI()		(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_CLK_DI()		(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_CLK_DI()		(RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_CLK_DI()		(RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_CLK_DI()		(RCC->AHB1ENR &= ~(1 << 7))

#define SYSCFG_CLK_DI()		(RCC->APB2ENR &= ~(1 << 14))

#define GPIOA_REG_RESET()	do{(RCC->AHB1RSTR |= (1 << 0));				(RCC->AHB1RSTR &= ~(1 << 0));}while(0)
#define GPIOB_REG_RESET()	do{(RCC->AHB1RSTR |= (1 << 1));				(RCC->AHB1RSTR &= ~(1 << 1));}while(0)
#define GPIOC_REG_RESET()	do{(RCC->AHB1RSTR |= (1 << 2));				(RCC->AHB1RSTR &= ~(1 << 2));}while(0)
#define GPIOD_REG_RESET()	do{(RCC->AHB1RSTR |= (1 << 3));				(RCC->AHB1RSTR &= ~(1 << 3));}while(0)
#define GPIOE_REG_RESET()	do{(RCC->AHB1RSTR |= (1 << 4));				(RCC->AHB1RSTR &= ~(1 << 4));}while(0)
#define GPIOF_REG_RESET()	do{(RCC->AHB1RSTR |= (1 << 5));				(RCC->AHB1RSTR &= ~(1 << 5));}while(0)
#define GPIOG_REG_RESET()	do{(RCC->AHB1RSTR |= (1 << 6));				(RCC->AHB1RSTR &= ~(1 << 6));}while(0)
#define GPIOH_REG_RESET()	do{(RCC->AHB1RSTR |= (1 << 7));				(RCC->AHB1RSTR &= ~(1 << 7));}while(0)

static inline uint8_t GPIO_BASEADDR_TO_CODE(GPIO_RegMap_t *pGPIOx) {
	return ((uint32_t)pGPIOx - 0x40020000) / 0x400;
}

#define EXTI0_IRQ			6
#define EXTI1_IRQ			7
#define EXTI2_IRQ			8
#define EXTI3_IRQ			9
#define EXTI4_IRQ			10
#define EXTI9_5_IRQ		23
#define EXTI15_10_IRQ	40

#endif
