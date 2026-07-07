#ifndef STM32F446XX_RCC_H_
#define STM32F446XX_RCC_H_

#include <stdint.h>

#define RCC_BASEADDR				(AHB1PERIPH_BASE + 0x3800)

typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t AHB3RSTR;
	volatile uint32_t RESERVED0;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t RESERVED1[2];
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;
	volatile uint32_t RESERVED3;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t RESERVED4[2];
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t AHB3LPENR;
	volatile uint32_t RESERVED5;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	volatile uint32_t RESERVED6[2];
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t RESERVED7[2];
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	volatile uint32_t PLLSAICFGR;
	volatile uint32_t DCKCFGR;
	volatile uint32_t CKGATENR;
	volatile uint32_t DCKCFGR2;
}RCC_RegMap_t;

#define RCC						((RCC_RegMap_t*) RCC_BASEADDR)

#endif
