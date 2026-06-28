#include "buzz_usart.h"
#include "buzz_rcc.h"

void USART_SetBaudData(USART_RegMap_t *pUSARTx, uint32_t BaudRate)
{
	uint32_t PCLKx;

	uint32_t usartdiv;

	uint32_t M_Part, F_Part;

	uint32_t tempreg = 0;

	if(pUSARTx == USART1 || pUSARTx == USART6)
	{
		PCLKx = RCC_GetPCLK2Value();
	}else
	{
		PCLKx = RCC_GetPCLK1Value();
	}

	// USARTDIV = APB 클럭(25 * PCLKx) / (Oversampling * BaudRate)
	if(pUSARTx->CR1 & USART_CR1_OVER8)
	{
		usartdiv = ((25 * PCLKx) / (2 * BaudRate));
	}else
	{
		usartdiv = ((25 * PCLKx) / (4 * BaudRate));
	}

	M_Part = usartdiv/100;

	tempreg |= M_Part << 4;

	F_Part = (usartdiv - (M_Part * 100));

	if(pUSARTx->CR1 & USART_CR1_OVER8)
	{
		F_Part = (((F_Part * 8) + 50) /100) & ((uint8_t)0x07);
	}else
	{
		F_Part = (((F_Part * 16) + 50) /100) & ((uint8_t)0x0F);
	}

	tempreg |= F_Part;

	pUSARTx->BRR = tempreg;
}


void USART_Init(USART_Handle_t *pUSARTHandle)
{
	// temporary variable
	uint32_t tempreg = 0;

	/* Configuration CR1 */

	// Implement the code to enable the Clock for given USART peripheral
	USART_PeriClockControl(pUSARTHandle->pUSARTx, ENABLE);

	//Enable USART Tx and Rx engines according to the USART_Mode configuration item
	if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_RX)
	{
		tempreg |= USART_CR1_RE;
	}else if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_TX)
	{
		tempreg |= USART_CR1_TE;
	}else if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TX_RX)
	{
		tempreg |= (USART_CR1_RE | USART_CR1_TE);
	}

	// Implement the code to configure the Word length configuration item
	tempreg |= pUSARTHandle->USART_Config.USART_WordLength << USART_CR1_M_Pos;

	//Configuration of parity control bit fields
	if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_EVEN)
	{
		tempreg |= USART_CR1_PCE;

		tempreg &= ~USART_CR1_PS;
	}else if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_ODD)
	{
		tempreg |= USART_CR1_PCE;

		tempreg |= USART_CR1_PS;
	}

	pUSARTHandle->pUSARTx->CR1 = tempreg;

	/* Configuration CR2 */

	tempreg = 0;

	//Implement the code to configure the number of stop bits inserted during USART frame transmission
	tempreg |= pUSARTHandle->USART_Config.USART_NoOfStopBits << USART_CR2_STOP_Pos;

	pUSARTHandle->pUSARTx->CR2 = tempreg;

	/* Configuration CR3 */

	tempreg = 0;

	//Configuration of USART hardware flow control
	if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
	{
		tempreg |= USART_CR3_CTSE;
	}else if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
	{
		tempreg |= USART_CR3_RTSE;
	}else if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
	{
		tempreg |= (USART_CR3_CTSE | USART_CR3_RTSE);
	}

	pUSARTHandle->pUSARTx->CR3 = tempreg;

	/*Configuration of BRR*/

	USART_SetBaudData(pUSARTHandle->pUSARTx, pUSARTHandle->USART_Config.USART_Baud);

	USART_PeripheralControl(pUSARTHandle->pUSARTx, ENABLE);
}

void USART_PeripheralControl(USART_RegMap_t *pUSARTx, uint8_t Cmd)
{
	if(Cmd == ENABLE)
	{
		pUSARTx->CR1 |= USART_CR1_UE;
	}else
	{
		pUSARTx->CR1 &= ~USART_CR1_UE;
	}
}

void USART_PeriClockControl(USART_RegMap_t *pUSARTx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pUSARTx == USART1)
		{
			USART1_CLK();
		}else if (pUSARTx == USART2)
		{
			USART2_CLK();
		}else if (pUSARTx == USART3)
		{
			USART3_CLK();
		}
		else if (pUSARTx == UART4)
		{
			UART4_CLK();
		}
		else if (pUSARTx == UART5)
		{
			UART5_CLK();
		}
		else if (pUSARTx == USART6)
		{
			USART6_CLK();
		}
	}
	else
	{
		//TODO
	}

}

uint8_t USART_GetFlagStatus(USART_RegMap_t *pUSARTx, uint8_t StatusFlagName)
{
	if(pUSARTx->SR & StatusFlagName)
	{
		return SET;
	}

	return RESET;
}


void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{
	uint16_t *pdata;

	for(uint32_t i = 0; i < Len ; i++ )
	{
		while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_SR_TXE));

		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
		{
			pdata = (uint16_t*) pTxBuffer;
			pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF);

			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				pTxBuffer++;
				pTxBuffer++;
			}
			else
			{
				pTxBuffer++;
			}
		}
		else
		{
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				pUSARTHandle->pUSARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
			}else
			{
				pUSARTHandle->pUSARTx->DR = (*pTxBuffer & (uint8_t)0x7F);
			}
			pTxBuffer++;
		}
	}

	while( ! USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_SR_TC));
}

void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
	for(uint32_t i = 0; i < Len ; i++ )
		{
			while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_SR_RXNE));

			if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
			{
				if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
				{
					*((uint16_t*) pRxBuffer) = (pUSARTHandle->pUSARTx->DR & (uint16_t)0x01FF);

					pRxBuffer++;
					pRxBuffer++;
				}
				else
				{
					*pRxBuffer = (pUSARTHandle->pUSARTx->DR & (uint8_t)0xFF);
					pRxBuffer++;
				}
			}
			else
			{
				if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
				{
					*pRxBuffer = (uint8_t) (pUSARTHandle->pUSARTx->DR & (uint8_t)0xFF);
				}
				else
				{
					*pRxBuffer = (uint8_t) (pUSARTHandle->pUSARTx->DR & (uint8_t)0x7F);
				}
				pRxBuffer++;
			}
		}
}

uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{
	uint8_t txstate = pUSARTHandle -> TxBusyState;

	if(txstate != USART_BUSY_IN_TX)
	{
		pUSARTHandle->TxLen = Len;
		pUSARTHandle->pTxBuffer = pTxBuffer;
		pUSARTHandle->TxBusyState = USART_BUSY_IN_TX;

		pUSARTHandle->pUSARTx->CR1 |= USART_CR1_TXEIE;

		pUSARTHandle->pUSARTx->CR1 |= USART_CR1_TCIE;
	}

	return txstate;
}


uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
	uint8_t rxstate = pUSARTHandle->RxBusyState;

	if(rxstate != USART_BUSY_IN_RX){
	pUSARTHandle->RxLen = Len;
	pUSARTHandle->pRxBuffer = pRxBuffer;
	pUSARTHandle->RxBusyState = USART_BUSY_IN_RX;

	(void)pUSARTHandle->pUSARTx->DR;

	pUSARTHandle->pUSARTx->CR1 |= USART_CR1_RXNEIE;
	}

	return rxstate;
}

void USART_ClearFlag(USART_RegMap_t *pUSARTx, uint16_t StatusFLagName)
{
	pUSARTx->SR &= ~(StatusFLagName);
}

void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{

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

void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
	*((volatile uint32_t*)(NVIC_IPR_BASE + iprx * 4)) |= (IRQPriority << shift_amount);
}

void USART_IRQHandling(USART_Handle_t *pUSARTHandle)
{
	if((pUSARTHandle->pUSARTx->SR & USART_SR_RXNE) && (pUSARTHandle->pUSARTx->CR1 & USART_CR1_RXNEIE))
	{
		*pUSARTHandle->pRxBuffer = pUSARTHandle->pUSARTx->DR & 0xFF;
		pUSARTHandle->pRxBuffer++;
		pUSARTHandle->RxLen--;
		if (pUSARTHandle->RxLen == 0)
		{
			pUSARTHandle->pUSARTx->CR1 &= ~USART_CR1_RXNEIE;
			USART_ApplicationEventCallback(pUSARTHandle, USART_EVENT_RX_CMPLT);
		}
	}

	if((pUSARTHandle->pUSARTx->SR & USART_SR_TC) && (pUSARTHandle->pUSARTx->CR1 & USART_CR1_TCIE))
	{
		if(pUSARTHandle->TxBusyState == USART_BUSY_IN_TX)
		{
			if(pUSARTHandle->TxLen == 0)
			{
				pUSARTHandle->pUSARTx->CR1 &= ~USART_CR1_TCIE;
				pUSARTHandle->TxBusyState = USART_READY;
				USART_ApplicationEventCallback(pUSARTHandle, USART_EVENT_TX_CMPLT);
			}
		}
	}

	if((pUSARTHandle->pUSARTx->SR & USART_SR_TXE) && (pUSARTHandle->pUSARTx->CR1 & USART_CR1_TXEIE))
	{
		if(pUSARTHandle->TxBusyState == USART_BUSY_IN_TX)
		{
			pUSARTHandle->pUSARTx->DR = *pUSARTHandle->pTxBuffer & 0xFF;
			pUSARTHandle->pTxBuffer++;
			pUSARTHandle->TxLen--;
		}
	}

	if(pUSARTHandle->pUSARTx->CR3 & USART_CR3_EIE)
	{
		if(pUSARTHandle->pUSARTx->SR & USART_SR_ORE)
		{
			USART_ApplicationEventCallback(pUSARTHandle, USART_ERR_ORE);
		}
	}
}

__attribute__((weak))
void USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle, uint8_t ApEv)
{

}
