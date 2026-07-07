#ifndef STM32F446XX_H_
#define STM32F446XX_H_

#include <stdint.h>

#define NVIC_ISER_BASE	0xE000E100UL
#define NVIC_ICER_BASE	0xE000E180UL
#define NVIC_IPR_BASE	0xE000E400UL

#define NO_PR_BITS_IMPLEMENTED			4

#define NVIC_ISER(n)		(*((volatile uint32_t*)(NVIC_ISER_BASE + (n)*4)))
#define NVIC_ICER(n)		(*((volatile uint32_t*)(NVIC_ICER_BASE + (n)*4)))
#define NVIC_IPR(n)		(*((volatile uint8_t*)(NVIC_IPR_BASE + (n))))

#define FLASH_BASEADDR	0x08000000UL

#define SRAM1_BASEADDR	0x20000000UL
#define SRAM2_BASEADDR	0x2001C000UL
#define ROM				0x1FFF0000UL
#define SRAM				SRAM1_BASEADDR

#define PERIPH_BASE		0x40000000UL
#define APB1PERIPH_BASE	PERIPH_BASE
#define APB2PERIPH_BASE	0x40010000UL
#define AHB1PERIPH_BASE 	0x40020000UL
#define AHB2PERIPH_BASE	0x50000000UL
#define AHB3PERIPH_BASE	0x60000000UL

#define ENABLE			1
#define DISABLE			0
#define SET				ENABLE
#define RESET				DISABLE
#define GPIO_PIN_SET		SET
#define GPIO_PIN_RESET	RESET

#include "stm32f446xx_rcc.h"
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_usart.h"
#include "stm32f446xx_i2c.h"


#endif
