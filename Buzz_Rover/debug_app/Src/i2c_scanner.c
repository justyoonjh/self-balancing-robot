#include "buzz_rcc.h"
#include "buzz_systick.h"
#include "stdio.h"
#include "i2c_scanner.h"

void I2C_AddressScan(I2C_Handle_t *pI2CHandle)
{
	for(uint8_t addr = 0; addr < 128; addr++)
	{
		I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

		while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB));

		pI2CHandle->pI2Cx->DR = (addr << 1);

		uint32_t timeout = 50000;
		while(!(pI2CHandle->pI2Cx->SR1 & (I2C_FLAG_ADDR | I2C_FLAG_AF)) && --timeout);

		if(pI2CHandle->pI2Cx->SR1 & I2C_FLAG_ADDR)
		{
			uint32_t dummy = pI2CHandle->pI2Cx->SR1;
			dummy = pI2CHandle->pI2Cx->SR2;
			(void)dummy;

			printf("Found device at 0x%02X\r\n", addr);
		}
		else
		{
			pI2CHandle->pI2Cx->SR1 &= ~I2C_FLAG_AF;
		}

		I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
	}
}
