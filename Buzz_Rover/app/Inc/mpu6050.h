#ifndef MPU6050_H
#define MPU6050_H

#include "buzz_i2c.h"

#define MPU6050_ADDR				0x68U

#define PWR_MGMT_1				0x6BU
#define WHO_AM_I					0x75U

void MPU6050_Init(I2C_Handle_t *pI2CHandle);
uint8_t MPU6050_ReadWhoAmI(I2C_Handle_t *pI2CHandle);

#endif
