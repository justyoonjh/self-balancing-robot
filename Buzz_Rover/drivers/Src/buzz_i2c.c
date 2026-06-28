#include "buzz_i2c.h"
#include "buzz_rcc.h"

void I2C_PeriClockControl(I2C_RegMap_t *pI2Cx, uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
		if(pI2Cx == I2C1) {I2C1_CLK();}
		else if(pI2Cx == I2C2) {I2C2_CLK();}
		else if(pI2Cx == I2C3) {I2C3_CLK();}
	}
	else
	{
		if(pI2Cx == I2C1) {I2C1_CLK_DI();}
		else if(pI2Cx == I2C2) {I2C2_CLK_DI();}
		else if(pI2Cx == I2C3) {I2C3_CLK_DI();}
	}
}

void I2C_Init(I2C_Handle_t *pI2CHandle)
{
	uint32_t tempreg = 0;
	// 1. 클럭 켜기 + CR1(ACK) 설정
	I2C_PeriClockControl(pI2CHandle->pI2Cx, ENABLE);

	tempreg |= pI2CHandle->I2C_Config.I2C_AckControl << I2C_CR1_ACK;
	pI2CHandle->pI2Cx->CR1 = tempreg;
	// 2. FREQ 필드 설정(몇 클럭인지 I2C 페리퍼럴에 전달)
	tempreg = 0;
	tempreg |= RCC_GetPCLK1Value() / 1000000;
	pI2CHandle->pI2Cx->CR2 = ((tempreg & 0x3F) << I2C_CR2_FREQ);
	pI2CHandle->pI2Cx->CR2 |= (1 << I2C_CR2_ITERREN);
	// 3. OAR1에 자기 주소 등록
	tempreg = 0;
	tempreg |= pI2CHandle->I2C_Config.I2C_DeviceAddress << I2C_OAR1_ADD;
	tempreg |= (1 << 14);
	pI2CHandle->pI2Cx->OAR1 = tempreg;

	uint16_t ccr_value = 0;
	tempreg = 0;

	if(pI2CHandle->I2C_Config.I2C_SCLspeed <= I2C_SCL_SPEED_SM)
	{
		ccr_value = RCC_GetPCLK1Value() / (2 * pI2CHandle->I2C_Config.I2C_SCLspeed);
		tempreg |= (ccr_value & 0xFFF);
	}
	else
	{
		tempreg |= ( 1 << I2C_CCR_SORF);
		tempreg |= (pI2CHandle->I2C_Config.FMDutyCycle << I2C_CCR_DUTY);

		if(pI2CHandle->I2C_Config.FMDutyCycle == I2C_FM_DUTY_2)
		{
			ccr_value = RCC_GetPCLK1Value() / (3 * pI2CHandle->I2C_Config.I2C_SCLspeed);
		}
		else
		{
			ccr_value = RCC_GetPCLK1Value() / (25 * pI2CHandle->I2C_Config.I2C_SCLspeed);
		}
		tempreg |= (ccr_value & 0xFFF);
	}
	pI2CHandle->pI2Cx->CCR = tempreg;

	if(pI2CHandle->I2C_Config.I2C_SCLspeed <= I2C_SCL_SPEED_SM)
	{
		tempreg = ((RCC_GetPCLK1Value() / 1000) * 300 / 1000000) + 1;
// 		tempreg = ((RCC_GetPCLK1Value() * 1000) / 1000000000) + 1;
	}
	else
	{
		tempreg = ((RCC_GetPCLK1Value() * 300) / 1000000000) + 1;
	}
	pI2CHandle->pI2Cx->TRISE = (tempreg & 0x3F);

	pI2CHandle->pI2Cx->FLTR = (I2C_FLTR_DNF & 0xF);
}

void I2C_PeripheralControl(I2C_RegMap_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pI2Cx->CR1 |= (1 << I2C_CR1_PE);
	}
	else
	{
		pI2Cx->CR1 &= ~(1 << I2C_CR1_PE);
	}
}

void I2C_GenerateStartCondition(I2C_RegMap_t *pI2Cx)
{
	pI2Cx->CR1 |= (1 << I2C_CR1_START);
}

void I2C_GenerateStopCondition(I2C_RegMap_t *pI2Cx)
{
	pI2Cx->CR1 |= (1 << I2C_CR1_STOP);
}

uint8_t I2C_GetFlagStatus(I2C_RegMap_t *pI2Cx, uint32_t FlagName)
{
	if(pI2Cx->SR1 & FlagName)
	{
		return SET;
	}
	return RESET;
}

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr)
{
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	while(!(pI2CHandle->pI2Cx->SR1 & (I2C_FLAG_SB | I2C_FLAG_AF)));
	if(pI2CHandle->pI2Cx->SR1 & I2C_FLAG_AF) goto handle_af;
	pI2CHandle->pI2Cx->DR = (SlaveAddr << 1);

	while(!(pI2CHandle->pI2Cx->SR1 & (I2C_FLAG_ADDR | I2C_FLAG_AF)));
	if(pI2CHandle->pI2Cx->SR1 & I2C_FLAG_AF) goto handle_af;
	(void)pI2CHandle->pI2Cx->SR1;
	(void)pI2CHandle->pI2Cx->SR2;

	while(Len > 0)
	{
		while(!(pI2CHandle->pI2Cx->SR1 & (I2C_FLAG_TXE | I2C_FLAG_AF)));
		if(pI2CHandle->pI2Cx->SR1 & I2C_FLAG_AF) goto handle_af;
		pI2CHandle->pI2Cx->DR = *pTxBuffer;
		pTxBuffer++;
		Len--;
	}

	while(!(pI2CHandle->pI2Cx->SR1 & (I2C_FLAG_BTF | I2C_FLAG_AF)));
	if(pI2CHandle->pI2Cx->SR1 & I2C_FLAG_AF) goto handle_af;

	if(Sr == I2C_DISABLE_SR)
	{
		I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
	}
	return;

handle_af:
	I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
	pI2CHandle->pI2Cx->SR1 &= ~I2C_FLAG_AF;
}

void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr)
{
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	while(!(pI2CHandle->pI2Cx->SR1 & (I2C_FLAG_SB | I2C_FLAG_AF)));
	if(pI2CHandle->pI2Cx->SR1 & I2C_FLAG_AF) goto handle_af;

	pI2CHandle->pI2Cx->DR = (SlaveAddr << 1) | 0x01;

	while(!(pI2CHandle->pI2Cx->SR1 & (I2C_FLAG_ADDR | I2C_FLAG_AF)));
	if(pI2CHandle->pI2Cx->SR1 & I2C_FLAG_AF) goto handle_af;

	if(Len == 1)
	{
		pI2CHandle->pI2Cx->CR1 &= ~(1 << I2C_CR1_ACK);
	}

	(void)pI2CHandle->pI2Cx->SR1;
	(void)pI2CHandle->pI2Cx->SR2;

	if(Len == 1)
	{
		I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
	}

	for(uint32_t i = Len; i > 0; i--)
	{
		while(!(pI2CHandle->pI2Cx->SR1 & (I2C_FLAG_RXNE | I2C_FLAG_AF)));
		if(pI2CHandle->pI2Cx->SR1 & I2C_FLAG_AF) goto handle_af;

		if(i == 2)
		{
			pI2CHandle->pI2Cx->CR1 &= ~(1 << I2C_CR1_ACK);
			if(Sr == I2C_DISABLE_SR)
			{
				I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
			}
		}

		*pRxBuffer = pI2CHandle->pI2Cx->DR;
		pRxBuffer++;
	}

	if(Sr == I2C_DISABLE_SR)
	{
		pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_ACK);
	}
	return;

handle_af:
	I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
	pI2CHandle->pI2Cx->SR1 &= ~I2C_FLAG_AF;
}




void I2C_ER_IRQHandling(I2C_Handle_t *pI2CHandle)
{
	uint32_t temp1, temp2;

	temp2 = pI2CHandle->pI2Cx->CR2 & (1 << I2C_CR2_ITERREN);

	temp1 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_BERR);
	if(temp1 && temp2)
	{
		pI2CHandle->pI2Cx->SR1 &= ~(1 << I2C_SR1_BERR);
		I2C_ApplicationEventCallback(pI2CHandle, I2C_ERROR_BERR);
	}

	temp1 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_ARLO);
	if(temp1 && temp2)
	{
		pI2CHandle->pI2Cx->SR1  &= ~(1 << I2C_SR1_ARLO);
		I2C_ApplicationEventCallback(pI2CHandle, I2C_ERROR_ARLO);
	}

	temp1 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_AF);
	if(temp1 && temp2)
	{
		pI2CHandle->pI2Cx->SR1 &= ~(1 << I2C_SR1_AF);
		I2C_ApplicationEventCallback(pI2CHandle, I2C_ERROR_AF);
	}

	temp1 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_OVR);
	if(temp1 && temp2)
	{
		pI2CHandle->pI2Cx->SR1 &= ~(1 << I2C_SR1_OVR);
		I2C_ApplicationEventCallback(pI2CHandle, I2C_ERROR_OVR);
	}

	temp1 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_TIMEOUT);
	if(temp1 && temp2)
	{
		pI2CHandle->pI2Cx->SR1 &= ~(1 << I2C_SR1_TIMEOUT);
		I2C_ApplicationEventCallback(pI2CHandle, I2C_ERROR_TIMEOUT);
	}
}

__attribute__((weak))
void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEv)
{

}
