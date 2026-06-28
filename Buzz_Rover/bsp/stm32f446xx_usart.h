#ifndef STM32F446XX_USART_H_
#define STM32F446XX_USART_H_

#include <stdint.h>

#define USART1_BASEADDR		(APB2PERIPH_BASE + 0x1000)
#define USART2_BASEADDR		(APB1PERIPH_BASE + 0x4400)
#define USART3_BASEADDR		(APB1PERIPH_BASE + 0x4800)
#define UART4_BASEADDR		(APB1PERIPH_BASE + 0x4C00)
#define UART5_BASEADDR		(APB1PERIPH_BASE + 0x5000)
#define USART6_BASEADDR		(APB2PERIPH_BASE + 0x1400)

typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}USART_RegMap_t;

#define USART1			((USART_RegMap_t*) USART1_BASEADDR)
#define USART2			((USART_RegMap_t*) USART2_BASEADDR)
#define USART3			((USART_RegMap_t*) USART3_BASEADDR)
#define UART4				((USART_RegMap_t*) UART4_BASEADDR)
#define UART5				((USART_RegMap_t*) UART5_BASEADDR)
#define USART6			((USART_RegMap_t*) USART6_BASEADDR)

#define USART1_CLK()		(RCC->APB2ENR |= (1 << 4))
#define USART2_CLK()		(RCC->APB1ENR |= (1 << 17))
#define USART3_CLK()		(RCC->APB1ENR |= (1 << 18))
#define UART4_CLK()		(RCC->APB1ENR |= (1 << 19))
#define UART5_CLK()		(RCC->APB1ENR |= (1 << 20))
#define USART6_CLK()		(RCC->APB2ENR |= (1 << 5))

#define USART1_CLK_DI()		(RCC->APB2ENR &= ~(1 << 4))
#define USART2_CLK_DI()		(RCC->APB1ENR &= ~(1 << 17))
#define USART3_CLK_DI()		(RCC->APB1ENR &= ~(1 << 18))
#define UART4_CLK_DI()		(RCC->APB1ENR &= ~(1 << 19))
#define UART5_CLK_DI()		(RCC->APB1ENR &= ~(1 << 20))
#define USART6_CLK_DI()		(RCC->APB2ENR &= ~(1 << 5))

#define USART_CR1_RE			(1 << 2)
#define USART_CR1_TE			(1 << 3)
#define USART_CR1_RXNEIE		(1 << 5)
#define USART_CR1_TCIE		(1 << 6)
#define USART_CR1_TXEIE		(1 << 7)
#define USART_CR1_PEIE		(1 << 8)
#define USART_CR1_PS			(1 << 9)
#define USART_CR1_PCE		(1 << 10)
#define USART_CR1_M			(1 << 12)
#define USART_CR1_M_Pos		12
#define USART_CR1_UE			(1 << 13)
#define USART_CR1_OVER8		(1 << 15)

#define USART_CR2_STOP_Pos	12
#define USART_CR2_STOP_Msk	(0x3 << USART_CR2_STOP_Pos)

#define USART_CR3_EIE		(1 << 0)
#define USART_CR3_RTSE		(1 << 8)
#define USART_CR3_CTSE		(1 << 9)
#define USART_CR3_CTSIE		(1 << 10)

#define USART_SR_PE			(1 << 0)
#define USART_SR_FE			(1 << 1)
#define USART_SR_NF			(1 << 2)
#define USART_SR_ORE			(1 << 3)
#define USART_SR_IDLE		(1 << 4)
#define USART_SR_RXNE		(1 << 5)
#define USART_SR_TC			(1 << 6)
#define USART_SR_TXE			(1 << 7)
#define USART_SR_LBD			(1 << 8)
#define USART_SR_CTS			(1 << 9)

#define USART1_IRQ		37
#define USART2_IRQ		38
#define USART3_IRQ		39
#define UART4_IRQ			52
#define UART5_IRQ			53
#define USART6_IRQ		71

#endif
