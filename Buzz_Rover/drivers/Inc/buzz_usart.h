#ifndef BUZZ_USART_H_
#define BUZZ_USART_H_

#include "stm32f446xx.h"

/*
 @USART_Mode
*/

typedef enum {
	USART_MODE_ONLY_TX,
	USART_MODE_ONLY_RX,
	USART_MODE_TX_RX
}Mode_t;
/*
 @USART_Baud
*/

#define USART_STD_BAUD_1200 1200
#define USART_STD_BAUD_2400 2400
#define USART_STD_BAUD_9600 9600
#define USART_STD_BAUD_19200 19200
#define USART_STD_BAUD_38400 38400
#define USART_STD_BAUD_57600 57600
#define USART_STD_BAUD_115200 115200
#define USART_STD_BAUD_230400 230400
#define USART_STD_BAUD_460800 460800
#define USART_STD_BAUD_921600 921600
#define USART_STD_BAUD_2M     2000000

/*
 @USART_ParityControl
*/

typedef enum {
	USART_PARITY_DISABLE,
	USART_PARITY_EN_EVEN,
	USART_PARITY_EN_ODD
}ParityControl_t;

/*
 @USART_WordLength
*/

typedef enum {
	USART_WORDLEN_8BITS,
	USART_WORDLEN_9BITS
}WordLength_t;

/*
 @USART_NoOfStopBits
*/

typedef enum {
	USART_STOPBITS_1,
	USART_STOPBITS_0_5,
	USART_STOPBITS_2,
	USART_STOPBITS_1_5
}NoOfStopBits_t;



/*
 @USART_HWFlowControl
*/

typedef enum {
	USART_HW_FLOW_CTRL_NONE,
	USART_HW_FLOW_CTRL_CTS,
	USART_HW_FLOW_CTRL_RTS,
	USART_HW_FLOW_CTRL_CTS_RTS
}HWFlowControl_t;

typedef struct
{
	Mode_t USART_Mode;
	uint32_t USART_Baud;
	NoOfStopBits_t USART_NoOfStopBits;
	WordLength_t USART_WordLength;
	ParityControl_t USART_ParityControl;
	HWFlowControl_t USART_HWFlowControl;
}USART_Config_t;

typedef struct
{
	USART_RegMap_t *pUSARTx;
	USART_Config_t USART_Config;
	uint8_t *pTxBuffer;
	uint8_t *pRxBuffer;
	uint32_t TxLen;
	uint32_t RxLen;
	uint8_t TxBusyState;
	uint8_t RxBusyState;
}USART_Handle_t;

/*
 Application states
*/

#define USART_BUSY_IN_RX 1
#define USART_BUSY_IN_TX 2
#define USART_READY 0

#define USART_EVENT_TX_CMPLT 0
#define USART_EVENT_RX_CMPLT 1
#define USART_EVENT_IDLE		2
#define USART_EVENT_CTS 		3
#define USART_EVENT_PE		4
#define USART_ERR_FE			5
#define USART_ERR_NE			6
#define USART_ERR_ORE		7

void USART_PeriClockControl(USART_RegMap_t *pUSARTx, uint8_t EnorDi);

void USART_Init(USART_Handle_t *pUSARTHandle);
void USART_DeInit(USART_Handle_t *pUSARTHandle);

void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);

void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void USART_IRQHandling(USART_Handle_t *pUSARTHandle);

uint8_t USART_GetFlagStatus(USART_RegMap_t *pUSARTx, uint8_t StatusFlagName);
void USART_ClearFlag(USART_RegMap_t *pUSARTx, uint16_t StatusFLagName);
void USART_PeripheralControl(USART_RegMap_t *pUSARTx, uint8_t EnorDi);
void USART_SetBaudData(USART_RegMap_t *pUSARTx, uint32_t BaudRate);

void USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle, uint8_t ApEv);


#endif
