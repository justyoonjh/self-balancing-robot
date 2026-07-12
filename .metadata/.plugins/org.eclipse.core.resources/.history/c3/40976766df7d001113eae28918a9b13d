#ifndef STM32F446XX_TIM_H_
#define STM32F446XX_TIM_H_

#define TIM2_BASEADDR 0x40000000

typedef struct
{
	volatile uint32_t CR1;		// Control Register 1
	volatile uint32_t CR2;
	volatile uint32_t SMCR;		// Slave Mode Control
	volatile uint32_t DIER;		// DMA/Interrupt Enable
	volatile uint32_t SR;		// Status Register
	volatile uint32_t EGR;		// Event Generation
	volatile uint32_t CCMR1;		// capture/compare mode register
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;		// capture/compare enable register
	volatile uint32_t CNT;		// counter
	volatile uint32_t PSC;		// prescaler
	volatile uint32_t ARR;		// auto-reload register
	uint32_t RESERVED0;
	volatile uint32_t CCR1;		// capture/compare register
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	uint32_t RESERVED1;
	volatile uint32_t DCR;		// DMA Control Register
	volatile uint32_t DMAR;		// DMA Address for full transfer
}TIM_RegMap_t;

#define TIM2		((TIM_RegMap_t*) TIM2_BASEADDR)

#define TIM2_PCLK_EN() (RCC->APB1ENR |= (1 << 0))

#endif
